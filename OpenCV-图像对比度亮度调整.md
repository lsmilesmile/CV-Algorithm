# 图像对比度亮度调整

> Felix
>
> 2022.9.26



###### 理论依据

算子的概念：

一般的图像处理算子都是一个函数，它接受一个或多个输入图像，并产生输出图像。下面是算子的一般形式：

![](./imgs/6.jpg)

调节亮度和对比度属于点操作，两种最常用的点操作是：乘上一个常数（对应对比度的调节）以及加上一个常数（对应亮度值的调节）。公式：

![](./imgs/7.jpg)

解析：

- f(x)表示源图像像素
- 参数g(x)表示输出图像像素
- 参数a（a>0）被称为增益，常常被用来控制图像的对比度
- 参数b通常被称为偏置，常常被用来控制图像的亮度

公式改写：

![](./imgs/8.jpg)

其中，i和j表示像素位于第i行和第j列。



###### 访问图像像素，执行：new_image(i, j) = a * image(i, j) + b：

code:

```c++
for (int y = 0; y < image.rows; y++)
{
    for (int x = 0; x < image.cols; x++)
    {
        for (int c = 0; c < 3; c++)
        {
            new_image.at<Vec3b>(y, x)[c] = 
                saturate_cast<uchar>((g_nContrastValue*0.01)*(image.at<Vec3b>(y, x)[c]) + 
                g_nBrightValue);
        }
    }
}
```



###### 调整亮度和对比度代码：

```c++
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

static void on_ContrastAndBright(int, void*);
static void ShowHelpText();

int g_nContrastValue;
int g_nBrightValue;
cv::Mat g_srcImage, g_dstImage;


int main()
{
	g_srcImage = cv::imread("./imgs/1.jpg");
	if (!g_srcImage.data)
	{
		printf("读取失败！\n");
		return -1;
	}
	g_dstImage = cv::Mat::zeros(g_srcImage.size(), g_srcImage.type());

	g_nContrastValue = 80;
	g_nBrightValue = 80;
	
	cv::namedWindow("xiaoguo", 1);

	cv::createTrackbar("对比度：", "xiaoguo", &g_nContrastValue, 300,
		on_ContrastAndBright);
	cv::createTrackbar("亮度：", "xiaoguo", &g_nBrightValue, 200,
		on_ContrastAndBright);

	on_ContrastAndBright(g_nContrastValue, 0);
	on_ContrastAndBright(g_nBrightValue, 0);

	while (char(cv::waitKey(1) != 'q')) {}
	return 0;
}

static void on_ContrastAndBright(int, void *)
{
	cv::namedWindow("yuanshi", 1);

	for (int y = 0; y < g_srcImage.rows; y++)
	{
		for (int x = 0; x < g_srcImage.cols; x++)
		{
			for (int c = 0; c < 3; c++)
			{
				g_dstImage.at<cv::Vec3b>(y, x)[c] =
					cv::saturate_cast<uchar>((g_nContrastValue*0.01)*(g_srcImage.at<cv::Vec3b>(y, x)[c])
						+ g_nBrightValue);
			}
		}
	}
	cv::imshow("yuanshi", g_srcImage);
	cv::imshow("xiaoguo", g_dstImage);
}
```

