/*
 * @Description: HSV2RGB && RGB2HSV
 * @Author: liuxiao
 * @Date: 2022-12-17 22:25:31
 */
#include <opencv2/opencv.hpp>
#include <math.h>
#include <iostream>

void RGB2HSV(unsigned char R, unsigned char G, unsigned char B, float& h, float& s, float& v);
void HSV2RGB(float h, float s, float v, unsigned char& R, unsigned char& G, unsigned char& B);
int clip3(int min, int max, int v);

int main() {
    cv::Mat src = cv::imread("./imgs/4.jpg");
    cv::imshow("src", src);
    for (int i = 0; i < src.rows; ++i) {
        for (int j = 0; j < src.cols; ++j) {
            float h, s, v;
            unsigned char R = src.at<cv::Vec3b>(i, j)[2];
            unsigned char G = src.at<cv::Vec3b>(i, j)[1];
            unsigned char B = src.at<cv::Vec3b>(i, j)[0];
            RGB2HSV(R, G, B, h, s, v);
            
            v *= 0.5;
            HSV2RGB(h, s, v, R, G, B);

            src.at<cv::Vec3b>(i, j)[0] = B;
            src.at<cv::Vec3b>(i, j)[1] = G;
            src.at<cv::Vec3b>(i, j)[2] = R;
        }
    }
    cv::imshow("trans", src);
    cv::waitKey();
    return 0;
}

int clip3(int min, int max, int v)
{
    int ret = v;
    if (ret < min)
        ret = min;
    if (ret > max)
        ret = max;
    return ret;
}

void RGB2HSV(unsigned char R, unsigned char G, unsigned char B, float& h, float& s, float& v) {
    // 归一化RGB值，
    float r = R / 255.0;
    float g = G / 255.0;
    float b = B / 255.0;

    // 求rgb最值
    float min, max;
    min = MIN(r, MIN(g, b));
    max = MAX(r, MAX(g, b));

    // 求h
    if (max == min)
        h = 0;
    else if(max == r && g >= b) 
        h = 60 * (g - b) / (max - min) + 0;
    else if (max == r && g < b)
        h = 60 * (g - b) / (max - min) + 360;
    else if (max == g)
        h = 60 * (b - r) / (max - min) + 120;
    else if (max == b)
        h = 60 * (r - g) / (max - min) + 240;
    
    // 防止超过范围
    h = clip3(0, 360, h);

    // 求s
    if (max == 0)
        s = 0;
    else
        s = (max - min) / max;

    // 求v
    v = max;

    

    
}

void HSV2RGB(float h, float s, float v, unsigned char& R, unsigned char& G, unsigned char& B) {
    float p = 0, q = 0, t = 0, f = 0, r = 0, g = 0, b = 0;
    int hN = 0;
    if (h == 360)
        h = 0;
    if (h < 0)
        h = 360 + h;

    hN = (int)((int)h / 60);
    f = h / 60.0f - hN;
    p = v * (1.0 - s);
    q = v * (1.0 - f * s);
    t = v * (1.0 - (1.0 - f) * s);

    switch (hN)
    {
    case 0:
        /* code */
        r = v; 
        g = t;
        b = p;
        break;
    case 1:
        r = q; 
        g = v;
        b = p;
        break;
    case 2:
        r = p;
        g = v;
        b = t;
        break;
    case 3:
        r = p;
        g = q;
        b = v;
        break;
    case 4:
        r = t;
        g = p;
        b = v;
        break;
    case 5:
        r = v;
        g = p;
        b = q;
        break;
    
    default:
        break;
    }

     R = (unsigned char)clip3(0, 255, (r * 255.0));
     G = (unsigned char)clip3(0, 255, (g * 255.0));
     B = (unsigned char)clip3(0, 255, (b * 255.0));
}