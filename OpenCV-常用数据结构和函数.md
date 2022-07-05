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



- **Point类**

  ```c++
  cv::Point point;
  point.x = 10;
  point.y = 4;
  // or
  cv::Point p2 = cv::Point(4, 4);
  
  // 定义
  typedef Point<int> Point2i;
  typedef Point2i Point;
  typedef Point_<float> Point2f;
  ```

  

- **Scalar类**

  颜色参数表达值

  ```c++
  cv::Scalar(a, b, c); // b, g, r
  ```

  

- **Size类**

  ```c++
  typedef Size_<int> Size2i;
  typedef Size2i Size;
  
  Size(3, 3);
  ```

  

- **Rect类**

  成员变量：x, y, width, height，分别表示：左上角点的坐标和矩形宽高。

  常用成员函数：

  **Size()返回Size；**

  **area()返回矩形的面积；**

  **contains(Point)判断点是否在矩形内；**

  **inside(Rect)函数判断矩形是否在该矩形内；**

  **tl()返回左上角点坐标；**

  **bt()返回右下角点坐标；**

  

  **求两个矩形的交并：**

  ```c++
  Rect rect = rect1 & rect2;
  Rect rect = rect1 | rect2;
  ```

  **让矩形进行平移或缩放操作：**

  ```c++
  Rect rectShift = rect + point;
  Rect rectScale = rect + size;
  ```
