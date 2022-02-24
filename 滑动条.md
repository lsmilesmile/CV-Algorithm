# OpenCV滑动条的使用

## API

**createTrackbar()**

```c++
#include<opencv2/highgui.hpp>
int cv:createTrackbar(const String &   trackbarname,
                      const String &   winname,
                      int *            value,
                      int              count,
                      TrackbarCallback conChange=0,
                      void*            userdata=0
                     )
```

创建一个滑动条并且绑定到特定的窗口

**Parameters**

- **trackbarname** 创建的滑动条的名字
- **winname**           作为滑动条父窗口的名字
- **value**                   可选的指向整型变量的指针，并且这个整形变量影响着滑动条的位置，一旦创建，滑动条的位置就会被这个变量定义
- **count**                  滑动条的最大位置，最小位置为0
- **onChange**           Pointer to the function to be called every time the slider changes position. This function should be prototyped as void Foo(int,void*); , where the first parameter is the trackbar position and the second parameter is the user data (see the next parameter). If the callback is the NULL pointer, no callbacks are called, but only value is updated.
- **userdata**             User data that is passed as is to the callback. It can be used to handletrack events without using global variables.



**addWeighted()**

```c++
#include <opencv2/core.hpp>
void cv::addWeighted(InputArray  src1,
                     double      alpha,
                     InputArray  src2,
                     double      beta,
                     double      gamma,
                     OutputArray dst,
                     int         dtype=-1
                    )
```

Calculates the weighted sum of two arrays.

The function addWeighted calculates the weighted sum of two arrays as follows:



​                                   **dst(I)=saturate(src1(I)∗alpha+src2(I)∗beta+gamma)**



where I is a multi-dimensional index of array elements. In case of multi-channel arrays, each channel is processed independently. The function can be replaced with a matrix expression:

**Parameters**

| src1  | first input array.                                           |
| ----- | ------------------------------------------------------------ |
| alpha | weight of the first array elements.                          |
| src2  | second input array of the same size and channel number as src1. |
| beta  | weight of the second array elements.                         |
| gamma | scalar added to each sum.                                    |
| dst   | output array that has the same size and number of channels as the input arrays. |
| dtype | optional depth of the output array; when both input arrays have the same depth, dtype can be set to -1, which will be equivalent to [src1.depth()](https://docs.opencv.org/4.4.0/d0/daf/group__projection.html#ga8b5e5413af41caf3f2a0bbf4cdf517a8). |



**getTrackbarPos()**

```c++
#include <opencv2/highgui.hpp>
int cv::getTrackbarPos(const String & trackbarname,
                       const String & winname
                       )
```

Return the trackbar position.

 The function returns the current position of the specified trackbar.

**Parameters**

| trackbarname |                 Name of the trackbar.                  |
| :----------: | :----------------------------------------------------: |
| **winname**  | Name of the window that is the parent of the trackbar. |

```c++
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

#define WINDOW_NAME "addweight"

const int g_nMaxAlphaValue = 100;
int g_nAlphaValueSlider; 
double g_dAlphaValue;
double g_dBetaValue;

cv::Mat g_srcImage1;
cv::Mat g_srcImage2;
cv::Mat g_dstImage;


void on_Trackbar(int, void*) {
	g_dAlphaValue = (double)g_nAlphaValueSlider / g_nMaxAlphaValue;
	g_dBetaValue = (1.0 - g_dAlphaValue);
	cv::addWeighted(g_srcImage1, g_dAlphaValue, g_srcImage2, g_dBetaValue, 0.0, g_dstImage);
	cv::imshow(WINDOW_NAME, g_dstImage);
}

int main(int argc, char ** argv) {
	g_srcImage1 = cv::imread("..\\imgs\\210818_1.jpg");
	g_srcImage2 = cv::imread("..\\imgs\\210818_2.jpg");
	if (g_srcImage1.empty()) {
		return -1;
	}
	if (!g_srcImage2.data) {
		return -1;
	}
	g_nAlphaValueSlider = 70;
	cv::namedWindow(WINDOW_NAME, 1);
	cv::String TrackbarName = "merge";
	cv::createTrackbar(TrackbarName, WINDOW_NAME, &g_nAlphaValueSlider, g_nMaxAlphaValue, on_Trackbar);
	on_Trackbar(g_nAlphaValueSlider, 0);
	cv::waitKey(0);
	return 0;
}
```

