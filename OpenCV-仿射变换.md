# 仿射变换

> Felix
>
> 2022.12.23



###### 含义

​    仿射变换（Affine Transformation），又称仿射映射，是指在几何中，一个向量空间进行一次线性变换并接上一个平移，变换为另一个向量空间的过程。它保持了二维图形的**平直性（直线经过变换后依然是直线）**和**平行性（二维图形之间的相对位置关系保持不变，平行线依然是平行线，且直线上的点的位置顺序不变）**。

​    一个任意的放射变换都能表示为乘以一个矩阵（线性变换）接着再加上一个向量（平移）的形式。

​    我们能够用放射变换来表示如下常见的三种变换形式：

- 旋转（线性变换）
- 平移（向量加）
- 缩放（线性变换）



###### OpenCV中仿射变换的使用

- 使用warpAffine来实现一些简单的重映射。
- 使用getRotationMareix2D来获得旋转矩阵。

warpAffine函数的作用是依据以下公式：

**dst(x, y) = src(M<sub>11</sub>x + M<sub>12</sub>y + M<sub>13</sub>, M<sub>21</sub>x + M<sub>22</sub>y + M<sub>23</sub>)**



###### 函数原型

**仿射变换**

```c++
void warapAffine(InputArray src, OutputArray dst, InputArray M, Size dsize, 
                int flags=INTER_LINEAR, int borderMode=BORDER_CONSTANT,
                const Scalar& borderValue=Scalar())
```

- src - 源图像，Mat类对象
- dst - 结果图像，和src有一样的尺寸和类型
- M - InputArray类型的M，2x3的变换矩阵
- Size- 表示输出图像的尺寸
- flags - 插值方法标识符。默认值INTER_LINEAR（线性插值）
- borderMode - 边界像素模式，默认是BORDER_CONSTANT
- borderValue，默认值Scalar()，即0



**计算二维旋转变换矩阵**

```c++
Mat getRotationMatrix2D(Point2f center, double angle, double scale)
```

- center - 源图像的旋转中心
- angle - 旋转角度。角度为正值表示向逆时针旋转（坐标原点是左上角）
- scale - 缩放系数

此函数计算以下矩阵：

![](./imgs/22.jpg)

其中：

![](./imgs/23.jpg)



###### code

```c++
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;
int main() {
	cv::Mat src;
	src = cv::imread("./imgs/1.jpg", cv::IMREAD_COLOR);
	if (src.empty()) {
		cout << "matTemplate Cannot load image" << endl;
		return -1;
	}
	cv::imshow("src", src);


	Point2f srcTri[3];
	srcTri[0] = Point2f(0.f, 0.f);
	srcTri[1] = Point2f(src.cols - 1.f, 0.f);
	srcTri[2] = Point2f(0.f, src.rows - 1.f);
	Point2f dstTri[3];
	dstTri[0] = Point2f(0.f, src.rows*0.33f);
	dstTri[1] = Point2f(src.cols*0.85f, src.rows*0.25f);
	dstTri[2] = Point2f(src.cols*0.15f, src.rows*0.7f);
	Mat warp_mat = getAffineTransform(srcTri, dstTri);
	Mat warp_dst = Mat::zeros(src.rows, src.cols, src.type());
	warpAffine(src, warp_dst, warp_mat, warp_dst.size());
	cv::imshow("warp_dst", warp_dst);

	Point center = Point(warp_dst.cols / 2, warp_dst.rows / 2);
	double angle = -50.0;
	double scale = 0.6;
	Mat rot_mat = getRotationMatrix2D(center, angle, scale);
	Mat warp_rotate_dst;
	warpAffine(warp_dst, warp_rotate_dst, rot_mat, warp_dst.size());
	cv::imshow("warp_rotate_dst", warp_rotate_dst);
	cv::waitKey();




	return 0;
}
```



**图像旋转**

```c++
#include <iostream>
#include <string>
#include <cmath>
#include <opencv2/opencv.hpp>
using std::sin;
using std::cos;

cv::Mat getRotationMatrix(cv::Point center, double angle, double scale)
{
	/*
	center : the center point of transform
	angle  : the angle of rotation
	scake  : the scale of zoom
	*/
	angle *= CV_PI / 180;//angle to rad
	double alpha = scale * cos(angle);
	double beta = scale * sin(angle);

	cv::Mat Matrix(2, 3, CV_64F);
	double *m = (double*)Matrix.data;
	m[0] = alpha;
	m[1] = beta;
	m[2] = (1 - alpha) * center.x - beta * center.y;
	m[3] = -beta;
	m[4] = alpha;
	m[5] = beta * center.x + (1 - alpha) * center.y;
	return Matrix;
}
int main(int argc, char* argv[])
{
	
	cv::Mat srcImage = cv::imread("./imgs/1.jpg");
	if (srcImage.empty())
	{
		std::cerr << "fail to load image" << std::endl;
		exit(-1);
	}

	cv::Point center(srcImage.rows / 2, srcImage.cols / 2);
	cv::Mat Mask = getRotationMatrix(center, 60, 1.0);
	cv::Mat dstImage(srcImage.size(), srcImage.type());
	cv::warpAffine(srcImage, dstImage, Mask, dstImage.size());

	cv::imshow("srcImage", srcImage);
	cv::imshow("dst", dstImage);
	cv::waitKey(0);
	cv::destroyAllWindows();
	return 0;
}
```

