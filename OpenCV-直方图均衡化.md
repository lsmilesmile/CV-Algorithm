# 直方图均衡化

> Felix
>
> 2022.12.23



###### 含义

​    用于图像增强。通过拉伸像素强度分布范围来增强图像对比度一种方法。均衡化处理后的图像只能是近似均匀分布。



###### api

```c++
void equalizeHist(InputArray src, OutputArray dst);
```

- src - 源图像，Mat类对象，8位单通道
- dst - 结果，和src相同的尺寸和类型



采用如下步骤对图像进行直方图均衡化：

1. 计算输入图像的直方图H

2. 直方图归一化，直方图的组距的和为255

3. 计算直方图积分：

   ![](./imgs/24.jpg)

4. 以H<sup>'</sup>作为查询表进行图像变换：

   **dst(x, y)=H<sup>'</sup>(src(x, y))**



###### code

```c++
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


int main() {

	cv::Mat srcImage, dstImage;
	srcImage = cv::imread("./imgs/1.jpg");

	if (!srcImage.data)
		return -1;

	cv::cvtColor(srcImage, srcImage, cv::COLOR_BGR2GRAY);
	cv::imshow("gray", srcImage);

	cv::equalizeHist(srcImage, dstImage);
	
	cv::imshow("dst", dstImage);

	cv::waitKey();

	return 0;
}
```

