/*
 * @Description: 
 * @Author: liuxiao
 * @Date: 2022-10-30 22:42:18
 */
#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <iostream>

int main()
{
    cv::Mat srcImage = cv::imread("./imgs/4.jpg", 0);
    if (srcImage.empty()) {
        printf("Read error!");
        return -1;
    }
    cv::imshow("src", srcImage);
    cv::waitKey();

    int m = cv::getOptimalDFTSize(srcImage.rows);
    int n = cv::getOptimalDFTSize(srcImage.cols);
    cv::Mat padded;
    cv::copyMakeBorder(srcImage, padded, 0, m - srcImage.rows, 0, n - srcImage.cols, 
    cv::BORDER_CONSTANT, cv::Scalar::all(0));
    cv::Mat planes[] = {cv::Mat_<float>(padded), 
    cv::Mat::zeros(padded.size(), CV_32F)};
    cv::Mat complexI;
    cv::merge(planes, 2, complexI);

    cv::dft(complexI, complexI);

    cv::split(complexI, planes);
    cv::magnitude(planes[0], planes[1], planes[0]);
    cv::Mat magnitudeImage = planes[0];

    magnitudeImage += cv::Scalar::all(1);
    cv::log(magnitudeImage, magnitudeImage);
    

    magnitudeImage = magnitudeImage(cv::Rect(0, 0, magnitudeImage.cols & -2,
    magnitudeImage.rows & -2));

    int cx = magnitudeImage.cols / 2;
    int cy = magnitudeImage.rows / 2;
    cv::Mat q0(magnitudeImage, cv::Rect(0, 0, cx, cy));
    cv::Mat q1(magnitudeImage, cv::Rect(cx, 0, cx, cy));
    cv::Mat q2(magnitudeImage, cv::Rect(0, cy, cx, cy));
    cv::Mat q3(magnitudeImage, cv::Rect(cx, cy, cx, cy));
    cv::Mat tmp;
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);

    cv::normalize(magnitudeImage, magnitudeImage, 0, 1, cv::NORM_MINMAX);
    cv::imshow("res", magnitudeImage);
    cv::waitKey();
    


    return 0;
}