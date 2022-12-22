# 霍夫变换

> Felix
>
> 2022.12.22



###### 标准霍夫变换

![](./imgs/19.jpg)



**code**

```c++
#include<opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void myHough(Mat src, Mat dst)
{
	vector<Vec2f> lines;//用于储存参数空间的交点
	HoughLines(src, lines, 1, CV_PI / 180, 120, 0, 0);//针对不同像素的图片注意调整阈值
	const int alpha = 1000;//alpha取得充分大，保证画出贯穿整个图片的直线
						   //lines中存储的是边缘直线在极坐标空间下的rho和theta值，在图像空间(直角坐标系下)只能体现出一个点
						   //以该点为基准，利用theta与斜率之间的关系，找出该直线上的其他两个点(可能不在图像上)，之后以这两点画出直线
	for (size_t i = 0; i < lines.size(); i++)
	{
		float rho = lines[i][0], theta = lines[i][1];
		double cs = cos(theta), sn = sin(theta);
		double x = rho * cs, y = rho * sn;
		Point pt1(cvRound(x + alpha * (-sn)), cvRound(y + alpha * cs));
		Point pt2(cvRound(x - alpha * (-sn)), cvRound(y - alpha * cs));
		line(dst, pt1, pt2, Scalar(0, 0, 255), 1, LINE_AA);
	}
}

int main()
{
	Mat mImage = imread("./imgs/1.jpg");
	if (mImage.data == 0)
	{
		cerr << "Image reading error !" << endl;
		system("pause");
	}
	namedWindow("The original image", WINDOW_NORMAL);
	imshow("The original image", mImage);

	Mat mMiddle;
	cvtColor(mImage, mMiddle, COLOR_BGR2GRAY);//Canny()只接受单通道8位图像，边缘检测前先将图像转换为灰度图
	Canny(mImage, mMiddle, 50, 150, 3);//边缘检测，检测结果作为霍夫变换的输入
	Mat mResult = mImage.clone();
	myHough(mMiddle, mResult);//将结果展示在原图像上
	namedWindow("The processed image", WINDOW_NORMAL);
	imshow("The processed image", mResult);
	waitKey();
	destroyAllWindows();
	return 0;
}
```



###### 累计霍夫概率变换

```c++
void HoughLinesP(InputArray image, OutputArray lines, double rho,
                double theta, int threshold, double minLineLength=0, double maxLineGap=0);
```

- image - 源图像，8位单通道二进制图像。
- lines - 经过调用HoughLinesP函数后存储了检测到的线条的输出矢量，每一条线由具有4哥矢量（x_1, y_1, x_2, y_2）表示，其中（x_1, y_1）和（x_2, y_2）是每个检测到的线段的结束点。
- rho - 以像素为单位的距离精度。或直线搜索时的进步尺寸的单位半径。
- theta - 以弧度位单位的角度精度。或直线搜索时的进步尺寸的单位角度。
- threshold - 累加平面的阈值参数，即识别某部分为图中的一条直线时它在累加平面中必须达到的值。大于阈值threshold的线段才可以被检测通过并返回到结果中。
- minLineLength - 默认值0，表示最低线段的长度，比这个设定参数短的线段就不能被显现出来。
- maxLineGap - 默认值0，允许将同一行点与点之间连接起来的最大距离。



**code**

```c++
#include<opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;


int main()
{
	cv::Mat srcImage = cv::imread("./imgs/1.jpg");
	cv::Mat midImage, dstImage;
	
	cv::Canny(srcImage, midImage, 50, 200, 3);
	cv::imshow("midImage", midImage);

	cv::cvtColor(midImage, dstImage, cv::COLOR_GRAY2BGR);

	std::vector<cv::Vec4i> lines;
	cv::HoughLinesP(midImage, lines, 1, CV_PI / 180, 80, 50, 10);

	for (size_t i = 0; i < lines.size(); i++) {
		cv::Vec4i l = lines[i];
		cv::line(dstImage, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]),
			cv::Scalar(186, 88, 255), 1, cv::LINE_AA);
	}

	cv::imshow("dstImage", dstImage);
	
	cv::waitKey();
	return 0;
}
```

