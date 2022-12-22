# 霍夫圆变换

> Felix
>
> 2022.12.22



###### api

![](./imgs/20.jpg)

![](./imgs/21.jpg)



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

	cv::cvtColor(srcImage, midImage, cv::COLOR_BGR2GRAY);

	cv::GaussianBlur(midImage, midImage, cv::Size(9, 9), 2, 2);

	std::vector<cv::Vec3f> circles;
	cv::HoughCircles(midImage, circles, cv::HOUGH_GRADIENT, 1.5,
		10, 200, 100, 0, 0);

	for (size_t i = 0; i < circles.size(); i++) {
		cv::Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		cv::circle(srcImage, center, radius, cv::Scalar(155, 50, 255), 3, 8, 0);
	}

	

	cv::imshow("dstImage", srcImage);
	
	cv::waitKey();
	return 0;
}
```



