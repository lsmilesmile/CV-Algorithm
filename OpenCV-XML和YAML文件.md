# OpenCV-XML和YAML文件

> Felix
>
> 2022.11.15
>
> birthday



## 简介

XML - 可扩展标识语言，一种语义/结构化语言，描述了文档的结构和语义。

YAML - 不是一种置标语言，可读性高，用来表达资料序列的格式。

后缀：.yml 或 .yaml



## FileStorage类

读取或写入XML或YAML文件的步骤

1. 实例化FileStorage类的对象，用默认带参数的构造函数完成初始化，或者用FileStorage::open()成员函数辅助初始化。
2. 使用流操作符<<进行文件写入操作，或者>>进行文件读取操作。
3. 使用FileStorage::release()函数析构掉FileStorage类对象，同时关闭文件。

代码步骤：

1. 文件写操作

   ```c++
   FileStorage::FileStorage();
   FileStorage::FileStorage(const string& source, int flags, const string& encoding=string())
   ```

   对于第二种带参数的构造函数：

   ```c++
   FileStorage fs("abc.xml", FileStorage::WRITE);
   ```

   对于第一种不带参数的构造函数，用FileStorage::open进行数据的写操作：

   ```c++
   FileStorage fs;
   fs.open("abc.xml", FileStorage::WRITE);
   ```

   

2. 文件读操作

   方式一

   ```c++
   FileStorage fs("abc.xml", FileStorage::READ);
   ```

   方式二

   ```c++
   FileStorage fs;
   fs.open("abc.xml", FileStorage::READ);
   ```

   

3. 文件读写操作

   - 文本和数字的输入和输出

     写入文件用 << 运算符

     ```c++
     fs << "iterationNr" << 100;
     ```

     读取文件 >> 

     ```c++
     int itNr;
     fs["iterationNr"] >> itNr;
     itNr = (int) fs["iterationNr"];
     ```

     

   - OpenCV数据数据结构的输入和输出

     ``` >> 
     cv::Mat R = cv::Mat_<uchar>::eye (3, 3);
     cv::Mat T = cv::Mat_<double>::zeros(3, 1);
     // 向Mat中写入数据
     fs << "R" << R;
     fs << "T" << T;
     // 从Mat中读取数据
     fs["R"] >> R;
     fs["T"] >> T;
     ```

     

4. vector(arrays)和maps的输入和输出

   对于vector结构，注意在第一个元素前加上"["，在最后一个元素前加上"]"。如：

   ```c++
   fs << "strings" << "[";
   fs << "image1.jpg" << "Awesomeness" << "baboom.jpg";
   fs << "]";
   ```

   而对于map结构，使用的符号是"{" 和 ”}“，如：

   ```c++
   fs <<"Mapping";
   fs << "{" << "One" << 1;
   fs << "Two" << 2 << "}";
   ```

   

5. 文件关闭

   文件关闭操作会在FilsStorage类销毁时自动进行，也可显示调用析构函数

   ```c++
   fs.realease();
   ```



## code

**文件写入**

```C++
#include <opencv2\opencv.hpp>
#include <time.h>
#include <iostream>


int main() {
	cv::FileStorage fs("test.yaml", cv::FileStorage::WRITE);

	fs << "frameCount" << 5;
	time_t rawtime; time(&rawtime);
	fs << "calibrationDate" << asctime(localtime(&rawtime));
	cv::Mat cameraMatrix = (cv::Mat_<double>(3, 3) << 1000, 0, 320, \
		0, 1000, 240, 0, 0, 1);
	cv::Mat disCoeffs = (cv::Mat_<double>(5, 1) << 0.1, 0.01, -0.001, 0, 0);
	fs << "cameraMatrix" << cameraMatrix << "distCoeffs" << disCoeffs;
	fs << "features" << "[";
	for (int i = 0; i < 3; i++) {
		int x = rand() % 640;
		int y = rand() % 480;
		uchar lbp = rand() % 256;
		fs << "{:" << "x" << x << "y" << y << "lbp" << "[:";
		for (int j = 0; j < 8; j++)
			fs << ((lbp >> j) & 1);
		fs << "]" << "}";
	}
	fs << "]";
	fs.release();

	printf("over.");
	getchar();
	return 0;
}
```

结果：

```
%YAML:1.0
---
frameCount: 5
calibrationDate: "Tue Dec 13 14:47:40 2022\n"
cameraMatrix: !!opencv-matrix
   rows: 3
   cols: 3
   dt: d
   data: [ 1000., 0., 320., 0., 1000., 240., 0., 0., 1. ]
distCoeffs: !!opencv-matrix
   rows: 5
   cols: 1
   dt: d
   data: [ 1.0000000000000001e-01, 1.0000000000000000e-02,
       -1.0000000000000000e-03, 0., 0. ]
features:
   - { x:41, y:227, lbp:[ 0, 1, 1, 1, 1, 1, 0, 1 ] }
   - { x:260, y:449, lbp:[ 0, 0, 1, 1, 0, 1, 1, 0 ] }
   - { x:598, y:78, lbp:[ 0, 1, 0, 0, 1, 0, 1, 0 ] }

```



**文件读取**

```c++
#include <opencv2\opencv.hpp>
#include <time.h>
#include <iostream>


int main() {
	system("color 6F");
	cv::FileStorage fs2("test.yaml", cv::FileStorage::READ);

	int frameCount = (int)fs2["frameCount"];

	std::string date;
	fs2["calibrationDate"] >> date;

	cv::Mat cameraMatrix2, distCoeffs2;
	fs2["cameraMatrix"] >> cameraMatrix2;
	fs2["distCoeffs"] >> distCoeffs2;

	std::cout << "frameCount: " << frameCount << std::endl \
		<< "calibration date: " << date << std::endl \
		<< "camera matrix: " << cameraMatrix2 << std::endl \
		<< "distortion coeffs: " << distCoeffs2 << std::endl;

	cv::FileNode features = fs2["features"];
	cv::FileNodeIterator it = features.begin(), it_end = features.end();
	int idx = 0;
	std::vector<uchar> lbpval;

	for (; it != it_end; ++it, idx++) {
		std::cout << "feature #" << idx << ": ";
		std::cout << "x=" << (int)(*it)["x"] << ", y=" << (int)(*it)["y"] << \
			", lbp: (";
		(*it)["lbp"] >> lbpval;
		for (int i = 0; i < (int)lbpval.size(); i++)
			std::cout << " " << (int)lbpval[i];
		std::cout << ")" << std::endl;
	}
	fs2.release();

	printf("over");
	getchar();
	return 0;
}
```

