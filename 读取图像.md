读取图像

**Api**

```c++
cv::Mat cv::imreaad(const cv::String& filename, int flags = cv::IMREAD_COLOR)
```

**Parameters**

- **filename** 文件名
- **flags**         读取模式(**cv::ImreadModes**)

常用的读取参数：

| Modes            | 解释                                                         |
| ---------------- | ------------------------------------------------------------ |
| IMREAD_GRAYSCALE | If set, always convert image to the single channel grayscale image (codec internal conversion). |
| IMREAD_COLOR     | If set, always convert image to the 3 channel BGR color image. |
| IMREAD_ANYDEPTH  | If set, return 16-bit/32-bit image when the input has the corresponding depth, otherwise convert it to 8-bit. |
| IMREAD_ANYCOLOR  | If set, the image is read in any possible color format.      |
| IMREAD_UNCHANGED | If set, return the loaded image as is (with alpha channel, otherwise it gets cropped). Ignore EXIF orientation. |

**code**

```c++
#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
	cv::Mat A = cv::imread(".\\imgs\\1.jpg", cv::IMREAD_GRAYSCALE);
	cv::imshow("A", A);
	cv::waitKey();
	system("pause");
	return 0;
}
```

