# 瘦脸

cpp

```c++
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <dlib/opencv.h>


#include <opencv2/opencv.hpp>
#include <opencv2/core/hal/interface.h>

#include <iostream>

#define MODEL_PATH "./models/shape_predictor_68_face_landmarks.dat"
#define RESIZE_RATIO 0.95


struct landmarkPos {
	int x;
	int y;
};

dlib::array2d<dlib::bgr_pixel> formatConvertOpencvToDlib(cv::Mat img)
{
	dlib::array2d<dlib::bgr_pixel> dMat_;
	assign_image(dMat_, dlib::cv_image<dlib::bgr_pixel>(img));
	return dMat_;
}

std::vector<std::vector<landmarkPos>> dlibFaceLandmarks(cv::Mat opencvImg)
{
	dlib::array2d<dlib::bgr_pixel> img = formatConvertOpencvToDlib(opencvImg);
	dlib::frontal_face_detector detector = dlib::get_frontal_face_detector();
	dlib::shape_predictor sp;
	dlib::deserialize(MODEL_PATH) >> sp;
	std::vector<dlib::rectangle> dets = detector(img);
	std::vector<std::vector<landmarkPos>> allLandmarks;
	for (unsigned long j = 0; j < dets.size(); ++j)
	{
		dlib::full_object_detection shape = sp(img, dets[j]);
		std::vector<landmarkPos> landmarksTemp;
		for (int i = 1; i < 16; i++)
		{
			landmarkPos temp;
			temp.x = shape.part(i - 1).x();
			temp.y = shape.part(i - 1).y();
			landmarksTemp.push_back(temp);
		}
		allLandmarks.push_back(landmarksTemp);
	}
	return allLandmarks;
}

cv::Mat resizeAndMerge(cv::Mat img)
{
	cv::Mat resized;
	cv::resize(img, resized, cv::Size(int(img.cols * RESIZE_RATIO), int(img.rows * RESIZE_RATIO)), 0, 0, cv::INTER_CUBIC);
	cv::Mat temp1(img.size(), CV_8UC3);
	int widthError = temp1.cols - resized.cols;
	int hightError = temp1.rows - resized.rows;
	// x, y, width, hight
	cv::Mat roi = temp1(cv::Rect(int(widthError / 2), int(hightError / 2), resized.cols, resized.rows));
	resized.copyTo(roi);
	return temp1;
}

std::array<int, 3> bilinearInsert(cv::Mat src, float ux, float uy)
{
	int w = src.cols;
	int h = src.rows;
	int c = src.channels();
	if (c == 3)
	{
		int x1 = (int)ux;
		int x2 = x1 + 1;
		int y1 = (int)uy;
		int y2 = y1 + 1;

		

		std::array<float, 3> part1;
		std::array<float, 3> part2;
		std::array<float, 3> part3;
		std::array<float, 3> part4;

		for (int channel = 0; channel < 3; channel++)
		{
			part1[channel] = float(src.at<cv::Vec3b>(y1, x1)[channel]) * ((float)x2 - ux) * ((float)y2 - uy);
			part2[channel] = float(src.at<cv::Vec3b>(y1, x2)[channel]) * (ux - (float)x1) * ((float)y2 - uy);
			part3[channel] = float(src.at<cv::Vec3b>(y2, x1)[channel]) * ((float)x2 - ux) * (uy - (float)y1);
			part4[channel] = float(src.at<cv::Vec3b>(y2, x2)[channel]) * (ux - (float)x1) * (uy - (float)y1);
		}

		std::array<int, 3> insertValue;
		for (int k = 0; k < 3; k++)
		{
			insertValue[k] = (int)part1[k] + (int)part2[k] + (int)part3[k] + (int)part4[k];
		}
		return insertValue;
	}
}

cv::Mat localTranslationWarp(cv::Mat srcImg, int startX, int startY, int endX, int endY, int radius)
{
	float ddradius = float(radius * radius);
	cv::Mat copyImg = srcImg.clone();

    int H = srcImg.rows;
	int W = srcImg.cols;
	int C = srcImg.channels();

	for (int i = 0; i < W; i++)
	{
		for (int j = 0; j < H; j++)
		{
			if (std::fabs(i - startX) > radius && std::fabs(j - startY) > radius)
				continue;

			float distance = (i - startX) * (i - startX) + (j - startY) * (j - startY);
			
			float ddmc = (i - endX) * (i - endX) + (j - endY) * (j - endY);

			if (distance < ddradius)
			{
				float ratio = (ddradius - distance) / (ddradius - distance + ddmc * (100 / 30));
				ratio = ratio * ratio;

				float UX = i - ratio * (endX - startX);
				float UY = j - ratio * (endY - startY);

				std::array<int, 3> value = bilinearInsert(srcImg, UX, UY);

				for (int c = 0; c < 3; c++)
				{
					copyImg.at<cv::Vec3b>(j, i)[c] = value[c];
				}
			}
		}
	}
	return copyImg;
}

cv::Mat thinFace(cv::Mat img)
{
	std::vector<std::vector<landmarkPos>> faceContour1 = dlibFaceLandmarks(img);
	cv::Mat resizedAndMergedImg = resizeAndMerge(img);
	std::vector<std::vector<landmarkPos>> faceContour2 = dlibFaceLandmarks(resizedAndMergedImg);
	cv::Mat thinedFace = img.clone();
	for (int i = 0; i < 15; i++)
	{
		thinedFace = localTranslationWarp(thinedFace,
			faceContour1[0][i].x, faceContour1[0][i].y,
			faceContour2[0][i].x, faceContour2[0][i].y,
			40);
	}
	return thinedFace;
}

cv::Mat largeEyes(cv::Mat img)
{
	return cv::Mat();
}

int main()
{
	std::string imgPath = "./testImgs/test3.jpg";
	cv::Mat src = cv::imread(imgPath, cv::IMREAD_COLOR);
	cv::imshow("src", src);
	cv::Mat thinedFace = thinFace(src);
	cv::imshow("thinedFace", thinedFace);
	cv::waitKey(0);


	system("pause");
	return 0;
}
```



py

```python
import cv2 as cv
import numpy as np
import math
import time

src = cv.imread("./test3.jpg", cv.IMREAD_COLOR)
b = False

startX = -1
startY = -1
endX = -1
endY = -1

pointPath = []

def localTranslationWarp(srcImg, startX, startY, endX, endY, radius):
    ddradius = float(radius * radius)
    copyImg = np.zeros(srcImg.shape, np.uint8)
    copyImg = srcImg.copy()

    # 计算公式中的|m-c|^2
    # ddmc = (endX - startX) * (endX - startX) + (endY - startY) * (endY - startY)
    H, W, C = srcImg.shape
    for i in range(W):
        for j in range(H):
            # 计算该点是否在形变圆的范围之内
            # 优化，第一步，直接判断是会在（startX,startY)的矩阵框中
            if math.fabs(i - startX) > radius and math.fabs(j - startY) > radius:
                continue

            distance = (i - startX) * (i - startX) + (j - startY) * (j - startY)

            ddmc = (i - endX) * (i - endX) + (j - endY) * (j - endY)

            if (distance < ddradius):
                # 计算出（i,j）坐标的原坐标
                # 计算公式中右边平方号里的部分
                ratio = (ddradius - distance) / (ddradius - distance + ddmc*(100 / 30))
                ratio = ratio * ratio

                # 映射原位置
                UX = i - ratio * (endX - startX)
                UY = j - ratio * (endY - startY)

                # 根据双线性插值法得到UX，UY的值
                value = BilinearInsert(srcImg, UX, UY)
                # 改变当前 i ，j的值
                copyImg[j, i] = value

    return copyImg


# 双线性插值法
def BilinearInsert(src, ux, uy):
    w, h, c = src.shape
    if c == 3:
        x1 = int(ux)
        x2 = x1 + 1
        y1 = int(uy)
        y2 = y1 + 1

        part1 = src[y1, x1].astype(np.float) * (float(x2) - ux) * (float(y2) - uy)
        part2 = src[y1, x2].astype(np.float) * (ux - float(x1)) * (float(y2) - uy)
        part3 = src[y2, x1].astype(np.float) * (float(x2) - ux) * (uy - float(y1))
        part4 = src[y2, x2].astype(np.float) * (ux - float(x1)) * (uy - float(y1))

        insertValue = part1 + part2 + part3 + part4

        return insertValue.astype(np.int8)


def fun(event, x, y, flags, param):
    global b     # 左键是否按下
    global startX
    global startY
    global endX
    global endY
    global pointPath

    if event == cv.EVENT_LBUTTONDOWN:
        startX = x
        startY = y
        # pointPath.clear()
        b = True

    elif event == cv.EVENT_LBUTTONUP:
        endX = x
        endY = y
        if b:
            global src
            print(startX, startY, end="\n")
            print(endX, endY, end="\n\n")
            src = localTranslationWarp(src, startX, startY, endX, endY, 80)
            cv.imshow('src', src)
            b = False


        # if b:

        #     global src
        #     if len(pointPath) % 2 == 0:
        #         for i in range(0, len(pointPath) - 1, 2):
        #             startX = pointPath[i][0]
        #             startY = pointPath[i][1]
        #             endX = pointPath[i + 1][0]
        #             endY = pointPath[i + 1][1]
        #             temp = src.copy()
        #             src = localTranslationWarp(temp, startX, startY, endX, endY, 70)
        #             cv.imshow('src', src)
        #             b = False
        #     elif len(pointPath) % 2 == 1:
        #         for i in range(1, len(pointPath) - 1, 2):
        #             startX = pointPath[i][0]
        #             startY = pointPath[i][1]
        #             endX = pointPath[i + 1][0]
        #             endY = pointPath[i + 1][1]
        #             temp = src.copy()
        #             src = localTranslationWarp(temp, startX, startY, endX, endY, 70)
        #             cv.imshow('src', src)
        #             b = False


    # elif event == cv.EVENT_MOUSEMOVE:
    #     if b:
    #         pointPath.append([x, y])



def main():
    cv.namedWindow("src")
    cv.imshow('src', src)
    cv.setMouseCallback("src", fun)
    # r = localTranslationWarp(src, 100, 100, 110, 110, 150)
    # cv.imwrite("r.jpg", r)
    cv.waitKey(0)


if __name__ == '__main__':
    main()

```



