# 图像ROI区域与融合

> Felix
>
> 2022.7.8



**定义ROI区域的方法**

- 方法1

  ```c++
  cv::Mat imageROI;
  imageROI = image(cv::Rect(50, 250, logo.cols, logs.rows))
  ```

  

- 方法2

  ```c++
  cv::Mat imageROI;
  imageROI = image(cv::Range(250, 250+logo.rows), cv::Range(50, 50+logo.cols));
  ```



**融合代码**

**copyTo()**

```c++


#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <bitset>


#ifdef _DEBUG
#pragma comment(lib, "opencv_world3410d.lib")
#else
#pragma comment(lib, "opencv_world3410.lib")
#endif // _DEBUG



int main()
{
	std::cout << "start..." << std::endl;

	cv::Mat src = cv::imread("src.jpg");
	cv::Mat tx = cv::imread("tx.jpg");
	if (src.empty() || tx.empty())
		return -1;
	cv::Mat roi = src(cv::Rect(20, 20, tx.cols, tx.rows));
	cv::Mat mask = cv::imread("tx.jpg", 0);
	tx.copyTo(roi, mask);
	cv::imshow("src", src);
	cv::waitKey();
	


	std::cout << "end." << std::endl;
	return 0;
}

```

