# copyTo

> Felix
>
> 2022.7.8



**函数原型**

```c++
void copyTo(OutputArray m) const;
void copyTo(OutputArray m, InputArray mask) const;
```

**参数**

输出图像

输出图像，掩码图

**示例**

```c++
image_in.copyTo(image_out);
```

把image_in这张图复制到image_out上



```c++
image_in.copyTo(image_out, mask);
```

这不仅是把image_in这张图复制到image_out上，且imge_in对应的mask中像素值位0的像素点都不会贴到image_out上。