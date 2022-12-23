# 图像轮廓

> Felix
>
> 2022.12.23



###### 寻找轮廓

findContours()函数用于在二值图像中寻找轮廓。

```c++
void findContours(InputArray image, OutputArrayOfArrays contours, OutputArray hierarchy,
                 int mode, int method, Point offset=Point());
```

- image - 源图像，Mat类对象，8位单通道。图像的非零像素被视为1，0像素被保留位0，所以图像为二进制。

- contours - 检测到的轮廓、函数调用后的结果存在这里。每个轮廓存储为一个点向量，即用point类型的vector表示。

- hierarchy - 可选的输出向量，包含图像的拓扑信息。其作为轮廓数量的表示，包含了许多元素。每个轮廓contours[i]对应4个hierarchy元素hierarchy\[i\][0]~hierarchy\[i\][3]，分别表示后一个轮廓、前一个轮廓，轮廓、内嵌轮廓的索引编号。

- mode - 轮廓检索模式：

  | **标识符**    | **含义**                                                     |
  | ------------- | ------------------------------------------------------------ |
  | RETR_EXTERNAL | 表示只检测最外层轮廓。对所有轮廓设置hierarchy\[i\][2]=hierarchy\[i\][3]=-1 |
  | RETR_LIST     | 提取所有轮廓，并且放在list中。检测到的轮廓不建立等级关系     |
  | RETR_CCOMP    | 提取所有轮廓，并且将其组织为双层结构，顶层为连通域的外围边界，次层为孔的内层边界 |
  | RETR_TREE     | 提取所有轮廓，并重新建立网状的轮廓结构                       |

- method - 为轮廓的近似办法，取值如下：

  | **标识符**                                   | 含义                                                         |
  | -------------------------------------------- | ------------------------------------------------------------ |
  | CHAIN_APPROX_NONE                            | 获取每个轮廓的每个像素，相邻的两个点的像素位置差不超过1，即max(abs(x1-x2), abs(y2-y1)) == 1 |
  | CHAIN_APPROX_SIMPLE                          | 压缩水平方向，垂直方向，对角线方向的元素，只保留该方向的终点坐标 |
  | CHAIN_APPROX_TC89_L1, CHAIN_APPROX_TC89_KCOS | 使用Teh-Chin1链逼近算法中的一个                              |

  

- offset - 每个轮廓点的可选偏移量，有默认值Point()。对ROI图像中找出的轮廓，并要在整个图像中进行分析时，可利用该参数。



###### 绘制轮廓

drawContours()函数用于在图像中绘制外部或内部轮廓。'

```c++
void drawContours(InputOutputArray image, InputArrayOfArrays contours,
                 int contourIdx, const Scalar& color, int thickness=1, 
                 int lineType=8, InputArray hierarchy=noArray(),
                 int maxLevel=INT_MAX, Point offset=Point());
```

- image - 目标图像，Mat类对象。
- contours - 所有的输入轮廓。每个轮廓存储为一个点向量，即point类型的vector表示。
- contourIdx - 轮廓绘制的指示变量。如果为负值，则绘制所有轮廓。
- color - 轮廓的颜色。
- thickness - 轮廓线条的粗细。
- lineType - 线条的类型
- hierarchy - 可选的层次结构信息，默认为noArray()。
- maxLevel - 用于绘制轮廓的最大等级，默认值INT_MAX。
- offset - 可选的轮廓偏移参数，用指定的偏移量offset=(dx, dy)偏移量需要绘制的轮廓，默认值Point()。
