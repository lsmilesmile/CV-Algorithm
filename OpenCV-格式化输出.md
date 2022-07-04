# 格式化输出

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

	cv::Mat r = cv::Mat(10, 3, CV_8UC3);
	cv::randu(r, cv::Scalar::all(0), cv::Scalar::all(255));

	// 输出
	// 默认风格
	std::cout << r << std::endl;

	// python 风格
	std::cout << cv::format(r, cv::Formatter::FMT_PYTHON) << std::endl;

	// 逗号分隔符风格
	std::cout << cv::format(r, cv::Formatter::FMT_CSV) << std::endl;

	// Numpy风格
	std::cout << cv::format(r, cv::Formatter::FMT_NUMPY) << std::endl;

	// C风格
	std::cout << cv::format(r, cv::Formatter::FMT_C) << std::endl;

	
	std::cout << "end." << std::endl;
	return 0;
}

```

