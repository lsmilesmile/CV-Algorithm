# 创建纯色图像

```c++
/*
 * @Description: 创建全白或者全黑图像
 * @Author: liuxiao
 * @Date: 2021-10-12 22:37:26
 */


#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char** argv) {
    cv::Mat whitePic_3channels(cv::Size(100, 100), CV_8UC3, cv::Scalar(255, 255, 255));
    cv::Mat blackPic_1channel(cv::Size(100, 100), CV_8UC1, cv::Scalar(0));
    cv::imshow("white", whitePic_3channels);
    cv::imshow("black", blackPic_1channel);
    cv::waitKey(); 
    return 0;
}

```

