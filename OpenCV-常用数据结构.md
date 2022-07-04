# 常用数据结构

> Felix
>
> 2022.7.4



**code:**

```c++


#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc_c.h>


#ifdef _DEBUG
#pragma comment(lib, "opencv_world3410d.lib")
#else
#pragma comment(lib, "opencv_world3410.lib")
#endif // _DEBUG


int main()
{
	std::cout << "start..." << std::endl;

	// 二维点
	cv::Point2f p(6, 2);
	std::cout << p << std::endl;

	// 三维点
	cv::Point3f p3f(8, 2, 0);
	std::cout << p3f << std::endl;

	// 基于Mat的vector
	std::vector<float> v;
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	std::cout << cv::Mat(v) << std::endl;

	// std::vector点
	std::vector<cv::Point2f> points(20);
	for (size_t i = 0; i < points.size(); ++i) {
		points[i] = cv::Point2f((float)(i * 5), (float)(i % 7));
	}
	std::cout << points << std::endl;
	
	std::cout << "end." << std::endl;
	return 0;
}

```

