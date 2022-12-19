/*
 * @Description: 
 * @Author: liuxiao
 * @Date: 2022-12-19 21:23:30
 */
#include <iostream>
#include <math.h>
#include <opencv2/opencv.hpp>

void RGB2YUV(unsigned char R, unsigned char G, unsigned char B, int& Y, int& U, int& V);
void YUV2RGB(int Y, int U, int V, unsigned char& R, unsigned char& G, unsigned char& B);

int clip3(int min, int max, int v)
{
    int ret = v;
    if (ret < min)
        ret = min;
    if (ret > max)
        ret = max;
    return ret;
}

int main() {
    cv::Mat src = cv::imread("./imgs/4.jpg");
    cv::imshow("src", src);
    cv::Mat MatY(src.size(), CV_8UC1);
    for (int i = 0; i < src.rows; ++i) {
        for (int j = 0; j < src.cols; ++j) {
            int Y, U, V;
            unsigned char B = src.at<cv::Vec3b>(i, j)[0];
            unsigned char G = src.at<cv::Vec3b>(i, j)[1];
            unsigned char R = src.at<cv::Vec3b>(i, j)[2];

            //std::cout << (int)R << ", " << (int)G << ", " << (int)B << std::endl;
            
            RGB2YUV(R, G, B, Y, U, V);
            U = (U + 122) / (double)(245) * 256;
            MatY.at<uchar>(i, j) = (uchar)U;
        }
    }
    cv::imshow("Y", MatY);
    cv::waitKey();
    return 0;
}


void RGB2YUV(unsigned char R, unsigned char G, unsigned char B, int& Y, int& U, int& V) {
    Y = (299 * R + 587 * G + 114 * B) / 1000;
    U = (-147 * R - 289 * G + 436 * B) / 1000;
    V = (615 * R - 515 * G - 100 * B) / 1000;
}

void YUV2RGB(int Y, int U, int V, unsigned char& R, unsigned char& G, unsigned char& B) {
    R = clip3(0, 255, (100 * Y + 114 * V) / 1000);
    G = clip3(0, 255, (1000 * Y - 395 * U - 581 * V) / 1000);
    B = clip3(0, 255, (1000 * Y + 2032 * U) / 1000);
}



