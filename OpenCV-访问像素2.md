# 访问像素

> Felix
>
> 2022.7.6



**code:**

```c++


#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


#ifdef _DEBUG
#pragma comment(lib, "opencv_world3410d.lib")
#else
#pragma comment(lib, "opencv_world3410.lib")
#endif // _DEBUG



int main()
{
	std::cout << "start..." << std::endl;

	
	cv::Mat src = cv::imread("test.jpg");
	int div = 32;

	// 指针访问像素
	int rowNumber = src.rows;
	int colNumber = src.cols * src.channels();
	for (int i = 0; i < rowNumber; i++) {
		// ptr是模板函数，返回任意行的首地址
		uchar* data = src.ptr<uchar>(i);
		for (int j = 0; j < colNumber; j++) {
			data[j] = data[j] / div * div + div / 2;
		}
	}

	// 迭代器操作像素
	cv::Mat_<cv::Vec3b>::iterator it = src.begin<cv::Vec3b>(); // 起始i位置
	cv::Mat_<cv::Vec3b>::iterator itend = src.end<cv::Vec3b>();// 终止位置
	for (; it != itend; ++it) {
		(*it)[0] = (*it)[0] / div * div + div / 2;
		(*it)[1] = (*it)[1] / div * div + div / 2;
		(*it)[2] = (*it)[2] / div * div + div / 2;
	}

	// 动态地址计算
	for (int i = 0; i < rowNumber; i++) {
		for (int j = 0; j < colNumber; j++) {
			src.at<cv::Vec3b>(i, j)[0] = \
				src.at<cv::Vec3b>(i, j)[0] / div * div + div / 2;
			src.at<cv::Vec3b>(i, j)[1] = \
				src.at<cv::Vec3b>(i, j)[1] / div * div + div / 2;
			src.at<cv::Vec3b>(i, j)[2] = \
				src.at<cv::Vec3b>(i, j)[2] / div * div + div / 2;
		}
	}


	std::cout << "end." << std::endl;
	return 0;
}

```

