# LUT函数

> Felix
>
> 2022.7.6



在缩减颜色空间中，我们先建好表，然后遍历像素再应用公式：

```c++
int divideWidth = 10;
uchar table[256];
for (int i = 0; i < 256; ++i) {
    table[i] = divideWidth * (i / divideWidth);
}
// 遍历像素：
p[j] = table[p[j]];
```

遍历像素的方式可以用LUT函数代替：

```c++
cv::Mat lookUpTable(1, 256, CV_8U);
uchar* p = lookUpTable.data;
for (int i = 0; i < 256; ++i) {
    p[i] = table[i];
}
// I:input,J:output
for (int i = 0; i < times; ++i) {
    LUT(I, lookUpTable, J);
}
```

