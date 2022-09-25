/*
 * @Description: addWeighted()
 * @Author: liuxiao
 * @Date: 2022-09-25 21:58:17
 */

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

bool ROI_AddImage();
bool LinearBlending();
bool ROI_LinearBlending();

int main()
{
    system("color 5E");
    
    if (ROI_AddImage() && LinearBlending() && ROI_LinearBlending())
    {
        std::cout << std::endl << "run ok.";
    }
    cv::waitKey(0);
    return 0;
}

bool ROI_AddImage()
{
    cv::Mat srcImage1 = cv::imread("./imgs/1.jpg");
    cv::Mat logoImage = cv::imread("./imgs/4.jpg");
    if (!srcImage1.data) 
    {
        printf("读取srcImage1错误!\n");
        return false;
    }
    if (!logoImage.data)
    {
        printf("读取logoImage错误!\n");
        return false;
    }
    cv::Mat imageROI = srcImage1(cv::Rect(200, 250, logoImage.cols, logoImage.rows));
    cv::Mat mask = cv::imread("./imgs/4.jpg", 0);
    logoImage.copyTo(imageROI, mask);
    cv::namedWindow("<1>利用ROI实现图像叠加示例窗口");
    cv::imshow("<1>利用ROI实现图像叠加示例窗口", srcImage1);

    return true;
}

bool LinearBlending()
{
    double alphaValue = 0.5;
    double betaValue;
    cv::Mat srcImage2, srcImage3, dstImage;

    srcImage2 = cv::imread("./imgs/1.jpg");
    srcImage3 = cv::imread("./imgs/2.jpg");

    if (!srcImage2.data)
    {
        printf("读取srcImage2错误!\n");
        return false;
    }
    if (!srcImage3.data)
    {
        printf("读取srcImage3错误\n");
        return false;
    }

    betaValue = 1.0 - alphaValue;
    cv::addWeighted(srcImage2, alphaValue, srcImage3, betaValue, 0.0, dstImage);
    cv::namedWindow("<2>线性混合示例窗口", 1);
    cv::imshow("<2>线性混合示例窗口", dstImage);
    cv::waitKey(0);
    return true;
}

bool ROI_LinearBlending()
{
    cv::Mat srcImage4 = cv::imread("./imgs/1.jpg", 1);
    cv::Mat logoImage = cv::imread("./imgs/4.jpg");
    if (!srcImage4.data)
    {
        printf("读取srcImage4错误.\n");
        return false;
    }
    if (!logoImage.data)
    {
        printf("读取logoImage错误.\n");
        return false;
    }

    cv::Mat imageROI;
    imageROI = srcImage4(cv::Rect(200, 250, logoImage.cols, logoImage.rows));
    //方法二
    //imageROI = srcImage4(cv::Range(250, 250+logoImage.rows), cv::Range(200, 200+logoImage.cols));
    cv::addWeighted(imageROI, 0.5, logoImage, 0.3, 0.0, imageROI);
    cv::imshow("rst", srcImage4);
    cv::waitKey(0);
    return true;
}
