# 重映射

> Felix
>
> 2022.12.23



###### 公式

​                                                     **dst(x,y)=src(map<sub>x</sub>(x,y), map<sub>y</sub>(x,y))** 



###### api

```c++
void remap(InputArray src, OutputArray dst, InputArray map1, InputArray map2,
          int interpolation, int borderMode=BORDER_CONSTANT, 
          const Scalar& borderValue=Scalar());
```

- src - Mat类对象，单通道8位或者浮点型图像。
- dst - 结果，和原图有一样的类型和尺寸。
- map1 - 它有两种可能表示的对象：
  - 表示点(x, y)的第一个映射。
  - 表示CV_16SC2、CV_32FC1、CV_32FC2类型的X值。
- map2 - 也有两种可能表示的对象，而且它会根据map1来确定表示哪种对象：
  - 若map1表示(x, y)时，这个参数不代表任何值。
  - 表示CV_16UC1, CV_32FC1类型的Y值（第二个值）。
- interpolation - 插值方式，**但是，resize()中的INTER_AREA的插值方式在这是不支持的。**插值方式有：
  - INTER_NEAREST - 最近邻插值
  - INTER_LINEAR - 双线性插值（默认值）
  - INTER_CUBIC - 双三次样条插值
  - INTER_LANCZOS4 - Lanczos插值
- borderMode - 边界模式，默认值BORDER_CONSTANT，表示目标图像中利群的点的像素值不会被修改
- const Scalar - 当有常数边界时使用的值



###### code

```c++
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

#define WINDOW_NAME "【程序窗口】"

cv::Mat g_srcImage, g_dstImage;
cv::Mat g_map_x, g_map_y;

int update_map(int key);

int main() {
	system("color 2F");

	g_srcImage = cv::imread("./imgs/1.jpg");
	if (!g_srcImage.data)
		return -1;
	g_dstImage.create(g_srcImage.size(), g_srcImage.type());
	g_map_x.create(g_srcImage.size(), CV_32FC1);
	g_map_y.create(g_srcImage.size(), CV_32FC1);

	cv::namedWindow(WINDOW_NAME, cv::WINDOW_AUTOSIZE);
	cv::imshow(WINDOW_NAME, g_srcImage);

	while (1) {
		int key = cv::waitKey();
		if (key & 255 == 27)
		{
			std::cout << "退出\n";
			break;
		}

		update_map(key);

		cv::remap(g_srcImage, g_dstImage, g_map_x, g_map_y,
			CV_INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar(0, 0, 0));
		cv::imshow(WINDOW_NAME, g_dstImage);
	}
	return 0;




	return 0;
}

int update_map(int key) {
	for (int j = 0; j < g_srcImage.rows; j++) {
		for (int i = 0; i < g_srcImage.cols; i++) {
			switch (key)
			{
			case '1':
				if (i > g_srcImage.cols * 0.25 && i < g_srcImage.cols * 0.75 \
					&& j > g_srcImage.rows*0.25 && j < g_srcImage.rows*0.75) {
					g_map_x.at<float>(j, i) = static_cast<float>(2 * (i - g_srcImage.cols*0.25) + 0.5);
					g_map_y.at<float>(j, i) = static_cast<float>(2 * (j - g_srcImage.rows*0.25) + 0.5);
				}
				else {
					g_map_x.at<float>(j, i) = 0;
					g_map_y.at<float>(j, i) = 0;
				}
				break;
			case '2':
				g_map_x.at<float>(j, i) = static_cast<float>(i);
				g_map_y.at<float>(j, i) = static_cast<float>(g_srcImage.rows - j);
				break;
			case '3':
				g_map_x.at<float>(j, i) = static_cast<float>(g_srcImage.cols - i);
				g_map_y.at<float>(j, i) = static_cast<float>(j);
				break;
			case '4':
				g_map_x.at<float>(j, i) = static_cast<float>(g_srcImage.cols - i);
				g_map_y.at<float>(j, i) = static_cast<float>(g_srcImage.rows - j);
				break;
			default:
				break;
			}
		}
	}
	return 1;
}
```







