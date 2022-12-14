# 方框滤波

> Felix
>
> 2022.12.13



###### 函数原型

```c++
void boxFilter(InputArray src, 
               OutputArray dst, 
               int depth, 
               Size ksize, 
               Point anchor=Point(-1, -1),
               boolnormalize=true,
               int borderType=BORDER_DEFAULT)
```

- 第一个参数，InputArray类型的src，输入图像，即源图像，填Mat类的对象即可。该函数对通道是独立处理的，且可以处理任意通道数的图片。但要注意，待处理的图片深度应该为CV_8U、CV_16U、CV_16S、CV_32F以及CV_64F之一。
- 第二个参数，OutputArray类型的dst，即目标图像，需要和源图片有一样的尺寸和类型。
- 第三个参数，int类型的depth，输出图像的深度，-1代表使用原图深度，即src.depth()。
- 第四个参数，Size类型的ksize，内核的大小。一般用Size(w,h)来表示内核的大小，其中w为像素宽度，h为像素高度。Size(3, 3)就表示3x3的核大小，Size(5, 5)就表示5x5的核大小。