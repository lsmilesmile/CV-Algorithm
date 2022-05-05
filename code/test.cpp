/*
 * @Description: 
 * @Author: liuxiao
 * @Date: 2022-04-13 21:07:23
 */

#include <iostream>
#include <opencv2/opencv.hpp>


int main() {
    cv::Mat src = cv::imread("C:/Users/lsmil/Pictures/Camera Roll/wife/30.jpg");
    cv::imshow("src", src);
    cv::waitKey();
    return 0;
}
