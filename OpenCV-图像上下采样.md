# 图像上下采样

> Felix
>
> 2022.12.22



###### 上采样

```c++
void pyrUp(InputArray src, OutputArray dst, const Size& dstsize=Size, 
          int borderType=BORDER_DEFAULT)
```

- 第一个参数，InputArray类型的src，输入图像，即源图像，填Mat类的对象即可。

- 第二个参数，OutputArray类型的dst，输出图像，和源图片有一样的尺寸和类型。

- 第三个参数，const Size&类型的dstsize，输出图像的大小；有默认值Size()，即默认情况下，由Size(src.cols\*2, src.rows\*2)来进行计算，且一直需要满足下列条件：

  **|dstsize.width-src.cols*2| <= (dstsize.width mod2)**

  **|dstsize.height-src.rows*2 <= (dstsize.height mod2)**

- 第四个参数，int类型的borderType，边界模式，一般不用去管他。

**code**

```c++
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

int main() {
	cv::Mat src = cv::imread("./imgs/1.jpg");
	cv::imshow("src", src);

	cv::Mat tmpImage, dstImage;
	tmpImage = src;
	cv::pyrUp(tmpImage, dstImage, cv::Size(tmpImage.cols * 2, tmpImage.rows * 2));
	cv::imshow("dst", dstImage);
	cv::waitKey();
	return 0;
}
```





###### 下采样

```c++
void pyrDown(InputArray src, OutputArray dst, const Size& dstsize=Size(), 
            int borderType=BORDER_DEFAULT)
```

- 第一个参数，InputArray类型的src，输入图像，即源图像，填Mat类的对象即可。

- 第二个参数，InputArray类型的dst，输出图像，和源图片有一样的尺寸和类型。

- 第三个参数，const Size&类型的dstsize，输出图像的大小；有默认值Size()，即默认情况下，由Size Size(src.cols+1)/2，(src.rows+1)/2来进行计算，且一直需要满足下列条件：

  **|dstsize.width*2-src.cols| <= 2**

  **|dstsize.height*2-src.rows| <= 2**

该pyrDown函数执行了高斯金字塔建造的向下采样的步骤。首先，它将源图像与如下内核做卷积运算：

![](./imgs/12.jpg)

接着，它通过对图像的偶数行和列做插值来进行向下采样操作。

**code**

```c++
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

int main() {
	cv::Mat src = cv::imread("./imgs/1.jpg");
	cv::imshow("src", src);

	cv::Mat tmpImage, dstImage;
	tmpImage = src;
	cv::pyrDown(tmpImage, dstImage, cv::Size(tmpImage.cols/ 2, tmpImage.rows / 2));
	cv::imshow("dst", dstImage);
	cv::waitKey();
	return 0;
}
```

