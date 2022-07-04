# 显式创建Mat的对象

> Felix
>
> 2022.7.4



- **使用Mat构造函数**

  ```c++
  cv::Mat M(2, 2, CV_8UC3, cv::Scalar(0, 0, 255));
  ```

  

- **在C/C++中通过构造函数初始化**

  ```c++
  int sz[3] = {2, 2, 2};
  cv::Mat L(3, sz, CV_8UC, cv::Scalar::all(0));
  ```

  

- **为已存在的IplImage指针创建信息头**

  ```c++
  IplImage* img = cvLoadImage("2.jpg", 1);
  cv::Mat mtx = cv::cvarrToMat(img);
  ```

  

- **利用Create()函数**

  ```c++
  cv::Mat M;
  M.create(4, 4, CV_8UC(2));
  ```

  

- **Matlab式的初始化方式**

  ```c++
  cv::Mat E = cv::Mat::eye(4, 4, CV_64F);
  
  cv::Mat O = cv::Mat::ones(2, 2, CV_32F);
  
  cv::Mat Z = cv::Mat::zeros(3, 3, CV_8UC1);
  ```

  

- **对小矩阵使用逗号分隔式初始化函数**

  ```c++
  cv::Mat c = (cv::Mat_<double>)(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
  ```

  

- **未已存在的对象创建信息头**

  ```c++
  cv::Mat RowClone = C.row(1).clone();
  ```

  