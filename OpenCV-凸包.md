# 凸包

> Felix
>
> 2022.12.28



###### 概念

​	凸包（Convex Hull）是一个计算几何中常见的概念。就是，给定二维平面上的点集，凸包就是将最外层的点连接起来构成的凸多边形，它是能包含点集中所有的点的。



###### 寻找凸包：convexHull()函数

```c++
void convexHull(InputArray points, OutputArray hull, bool clockwise=false, 
               bool returnPoints=true);
```

- points - 输入的二维点集，Mat类型或者std::vector
- hull - 输出参数，函数调用后找到的凸包
- clockwise - 操作方向标识符。为真时，输出的凸包为顺时针方向，否则就是逆时针方向。并且是假定坐标系的x轴指向右，y轴指向上方。
- returnPoints，操作标识符，默认值true。当为真时，函数返回各凸包的各个点。否则，它返回凸包各点的指数。当输出的数组是std::vector时，此标识被忽略。



###### code

```c++

```

