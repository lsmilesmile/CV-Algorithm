/*
 * @Description: 阈值化
 * @Author: liuxiao
 * @Date: 2022-12-20 21:50:34
 */
#include <iostream>
#include <opencv2/opencv.hpp>

void threshold(const cv::Mat& src, cv::Mat& dst, int threVal);

int main() {
    cv::Mat src = cv::imread("./imgs/4.jpg");
    cv::imshow("src", src);
    cv::waitKey();
    cv::Mat dst(src.size(), CV_8UC1);
    threshold(src, dst, 100);
    cv::imshow("dst", dst);
    cv::waitKey();
    return 0;
}

void threshold(const cv::Mat& src, cv::Mat& dst, int threVal) {
    if (dst.channels() != 1){
        std::cout << "img error.\n";
        return;
    }
    uchar B, G, R, gray;
    for (int i = 0; i < src.rows; ++i) {
        for (int j = 0;j < src.cols; ++j) {
            B = src.at<cv::Vec3b>(i, j)[0];
            G = src.at<cv::Vec3b>(i, j)[1];
            R = src.at<cv::Vec3b>(i, j)[2];
            gray = (B + G + R) / 3;
            gray = gray < threVal ? 0 : 255;
            dst.at<uchar>(i, j) = gray;
        }
    }
}