# 遍历像素

```c++
/*
 * @Description: 遍历像素
 * @Author: liuxiao
 * @Date: 2021-10-11 21:54:42
 */


#include <iostream>
#include <opencv2/opencv.hpp>


/**
 * @Brief:       像素遍历，实现灰度化
 * @param image: 图片
 * @return:
 */
void traversePixelsThreeChannels_1(cv::Mat& image) {
    cv::Mat grayscale(image.size(), CV_8UC1);
    for (int r = 0; r < image.rows; r++) {
        for (int c = 0; c < image.cols; c++) {
            // cv::saturate_cast 防止值溢出
            grayscale.at<uchar>(r, c) = cv::saturate_cast<uchar>((image.at<cv::Vec3b>(r, c)[0] + 
                                                                 image.at<cv::Vec3b>(r, c)[1] + 
                                                                 image.at<cv::Vec3b>(r, c)[2]) / 3);
        }
    }
    cv::imshow("grayscale", grayscale);
    cv::waitKey();
}

void traversePixelsThreeChannels_2(cv::Mat& image) {
    int rowNum = image.rows;
    int colNum = image.cols * image.channels();
    cv::Mat grayscale(image.size(), CV_8UC1);
    for (int r = 0; r < rowNum; r++) {
        uchar* pixPtr1 = image.ptr<uchar>(r);
        uchar* pixPtr2 = grayscale.ptr<uchar>(r);
        for (int c = 0; c < colNum; c+=3) {
            pixPtr2[c/3] = cv::saturate_cast<uchar>((pixPtr1[c] + pixPtr1[c+1] + pixPtr1[c+2]) / 3);
        }
    }
    cv::imshow("grayscale", grayscale);
    cv::waitKey();
}

void traversePixelsThreeChannels_3(cv::Mat& image) {
    int rowNum = image.rows;
    int colNum = image.cols;
    cv::Mat grayscale(image.size(), CV_8UC1);
    for (int r = 0; r < rowNum; r++) {
        cv::Vec3b *rowPointer1 = image.ptr<cv::Vec3b>(r);
        uchar *rowPointer2 = grayscale.ptr<uchar>(r);
        for (int c = 0; c < colNum; c++) {
            rowPointer2[c] = cv::saturate_cast<uchar>((rowPointer1[c][0] + rowPointer1[c][1] + rowPointer1[c][2]) / 3);
        }
    }
    cv::imshow("grayscale", grayscale);
    cv::waitKey();
}

void traversePixelsThreeChannels_4(cv::Mat& image) {
    cv::Mat_<cv::Vec3b>::iterator it = image.begin<cv::Vec3b>();
    cv::Mat_<cv::Vec3b>::iterator itend = image.end<cv::Vec3b>();
    cv::Mat grayscale(image.size(), CV_8UC1);
    cv::Mat_<uchar>::iterator it2 = grayscale.begin<uchar>();
    cv::Mat_<uchar>::iterator it2end = grayscale.end<uchar>();
    for (; it != itend, it2 != it2end; ++it, ++it2) {
        (*it2) = cv::saturate_cast<uchar>((((*it)[0]) + ((*it)[1]) + ((*it)[2])) / 3);
    }
    cv::imshow("grayscale", grayscale);
    cv::waitKey();
}

/**
 * @Brief:       单通道遍历 可以借鉴3通道的写法
 * @param image: single channel image
 * @return
 */
void traversePixelsSingleChannels_1(cv::Mat& image) {
    for (int r = 0; r < image.rows; r++) {
        for (int c = 0; c < image.cols; c++) {
            image.at<uchar>(r, c) = 255 - image.at<uchar>(r, c);
        }
    }
    cv::imshow("invert", image);
    cv::waitKey();
}


int main(int argc, char** argv) {
    cv::Mat image = cv::imread("./imgs/1.jpg");

    // three channels
    // traversePixelsThreeChannels_1(image);
    // traversePixelsThreeChannels_2(image);
    // traversePixelsThreeChannels_3(image);
    //traversePixelsThreeChannels_4(image);
    
    // single channel
    cv::Mat image2 = cv::imread("./imgs/1.jpg", cv::IMREAD_GRAYSCALE);
    traversePixelsSingleChannels_1(image2);

    std::cin.get();
    return 0;
}

```

