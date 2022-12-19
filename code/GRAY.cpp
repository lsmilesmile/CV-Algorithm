/*
 * @Description: 图像灰度化
 * @Author: liuxiao
 * @Date: 2022-12-19 23:02:46
 */

/*
 * 图像灰度化：
 *    - 均值灰度化
 *      Gray = (R + G + B) / 3
 *    - 经典灰度化
 *      Gray = 0.299R + 0.587G + 0.114B
 *    - Photoshop灰度化
 *      Gray = 
 *             max(R, G, B) + min(R, G, B)
 *            ----------------------------
 *                         2
*/

#include <iostream>
#include <math.h>
#include <opencv2/opencv.hpp>


void averageGray(cv::Mat& src, cv::Mat& dst);
void classicGray(cv::Mat& src, cv::Mat& dst);
void photoshopGray(cv::Mat& src, cv::Mat& dst);


int main() {
    cv::Mat src = cv::imread("./imgs/4.jpg");
    cv::imshow("src", src);
    cv::Mat dst(src.size(), CV_8UC1);
    photoshopGray(src, dst);
    cv::imshow("dst", dst);
    cv::waitKey();
    return 0;
}

void averageGray(cv::Mat& src, cv::Mat& dst) {
    for (int i = 0; i < src.rows; ++i) {
        for (int j = 0; j < src.cols; ++j) {
            uchar B = src.at<cv::Vec3b>(i, j)[0];
            uchar G = src.at<cv::Vec3b>(i, j)[1];
            uchar R = src.at<cv::Vec3b>(i, j)[2];
            dst.at<uchar>(i, j) = (R + G + B) / 3;
        }
    }
}

void classicGray(cv::Mat& src, cv::Mat& dst) {
    for (int i = 0; i < src.rows; ++i) {
        for (int j = 0; j < src.cols; ++j) {
            uchar B = src.at<cv::Vec3b>(i, j)[0];
            uchar G = src.at<cv::Vec3b>(i, j)[1];
            uchar R = src.at<cv::Vec3b>(i, j)[2];
            dst.at<uchar>(i, j) = (uchar)(0.299 * R + 0.587 * G + 0.114 * B);
        }
    }
}

void photoshopGray(cv::Mat& src, cv::Mat& dst) {
    for (int i = 0; i < src.rows; ++i) {
        for (int j = 0; j < src.cols; ++j) {
            uchar B = src.at<cv::Vec3b>(i, j)[0];
            uchar G = src.at<cv::Vec3b>(i, j)[1];
            uchar R = src.at<cv::Vec3b>(i, j)[2];
            uchar maxval = MAX(B, MAX(G, R));
            uchar minval = MIN(B, MIN(G, R));
            dst.at<uchar>(i, j) = (maxval + minval) / 2;
        }
    }
}
 