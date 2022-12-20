/*
 * @Description: ps亮度对比度调节
 * @Author: liuxiao
 * @Date: 2022-12-20 22:10:52
 */
#include <iostream>
#include <opencv2/opencv.hpp>
#include <cstdio>

const int UPVAL = 100;
const int DOWNVAL = -100;

int clip3(int v, int min, int max);

void adjustBrightAndContrast(const cv::Mat& src, cv::Mat& dst, int bright, int contrast);

void f_BrightContrast(unsigned char* srcData, int width, int height, int stride, int birght, int contrast);

int main() {
    cv::Mat src = cv::imread("./imgs/4.jpg");
    int birght = 0;
    int contrast = 90;
    cv::Mat dst(src.size(), src.type());
    adjustBrightAndContrast(src, dst, birght, contrast);
    cv::imshow("dst", dst);
    cv::waitKey();
    return 0;
}

int clip3(int v, int min, int max)
{
    int ret = v;
    if (ret < min)
        ret = min;
    if (ret > max)
        ret = max;
    return ret;
}


void adjustBrightAndContrast(const cv::Mat& src, cv::Mat& dst, int bright, int contrast) {
    bright = clip3(bright, DOWNVAL, UPVAL);
    contrast  =clip3(bright, DOWNVAL, UPVAL);
    int sum = 0;
    for (int i = 0; i < src.rows; ++i) {
        for (int j = 0; j < src.cols; ++j) {
            uchar gray = (299 * src.at<cv::Vec3b>(i, j)[2] + 587 * src.at<cv::Vec3b>(i, j)[1] + 114 * src.at<cv::Vec3b>(i, j)[0]) / 1000;
            sum += gray;
        }
    }
    int averageGray = sum / (src.rows * src.cols);
    int temp = 0;
    uchar BC_MAP[256];
    for (int i = 0; i < 256; ++i) {
        int temp = contrast > 0 ? clip3(i + bright, 0, 255) : i; 
        if (contrast > 0) {
            temp = clip3(i + bright, 0, 255);
            temp = clip3(averageGray + (temp - averageGray) * (1.0f / (1.0f - contrast / 100.0f)), 0, 255);
        } else {
            temp = i;
            temp = clip3(averageGray + (temp - averageGray) * (1.0f + contrast / 100.0f), 0, 255);
            temp = clip3(temp + bright, 0, 255);
        }
        BC_MAP[i] = temp;
    }

    for (int i = 0; i < src.rows; ++i) {
        for (int j = 0; j < src.cols; ++j) {
            dst.at<cv::Vec3b>(i, j)[0] = BC_MAP[src.at<cv::Vec3b>(i, j)[0]];
            dst.at<cv::Vec3b>(i, j)[1] = BC_MAP[src.at<cv::Vec3b>(i, j)[1]];
            dst.at<cv::Vec3b>(i, j)[2] = BC_MAP[src.at<cv::Vec3b>(i, j)[2]];

        }
    }

}