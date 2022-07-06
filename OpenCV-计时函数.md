# 计时函数

> Felix
>
> 2022.7.6



- **getTickCount() - 返回CPU自某个事件以来走过的时钟周期数。**
- **getTickFrequency() - 返回CPU一秒所走过的时钟周期数。**



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

	double start = static_cast<double>(cv::getTickCount());
	cv::Mat src = cv::imread("test.jpg");
	if (src.isSubmatrix())
		std::cout << "1" << std::endl;
	start = ((double)cv::getTickCount() - start) / cv::getTickFrequency();
	std::cout << start << std::endl;


	std::cout << "end." << std::endl;
	return 0;
}

```

