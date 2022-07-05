# 基本图形绘制

> Felix
>
> 2022.7.5



**code:**

```c++


#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


#ifdef _DEBUG
#pragma comment(lib, "opencv_world3410d.lib")
#else
#pragma comment(lib, "opencv_world3410.lib")
#endif // _DEBUG

#define WINDOW_NAME1 "[win1]"
#define WINDOE_NAME2 "[win2]"
#define WINDOW_WIDTH 600

void DrawEllipse(cv::Mat img, double angle) {
	int thickness = 2;
	int lineType = 8;

	cv::ellipse(img,
		cv::Point(WINDOW_WIDTH / 2, WINDOW_WIDTH / 2),
		cv::Size(WINDOW_WIDTH / 4, WINDOW_WIDTH / 16),
		angle,
		0,
		360,
		cv::Scalar(255, 129, 0),
		thickness,
		lineType);
}

void DrawFilledCircle(cv::Mat img, cv::Point center) {
	int thickness = -1;
	int lineType = 8;

	cv::circle(img,
		center,
		WINDOW_WIDTH / 32,
		cv::Scalar(0, 0, 255),
		thickness,
		lineType);
}

void DrawPolygon(cv::Mat img) {
	int lineType = 8;

	cv::Point rookPoints[1][20];
	rookPoints[0][0] = cv::Point(WINDOW_WIDTH / 4, 7 * WINDOW_WIDTH / 8);
	rookPoints[0][1] = cv::Point(3 * WINDOW_WIDTH / 4, 7 * WINDOW_WIDTH / 8);
	rookPoints[0][2] = cv::Point(3 * WINDOW_WIDTH / 4, 13 * WINDOW_WIDTH / 16);
	rookPoints[0][3] = cv::Point(11 * WINDOW_WIDTH / 16, 13 * WINDOW_WIDTH / 16);
	rookPoints[0][4] = cv::Point(19 * WINDOW_WIDTH / 32, 3 * WINDOW_WIDTH / 8);
	rookPoints[0][5] = cv::Point(3 * WINDOW_WIDTH / 4, 3 * WINDOW_WIDTH / 8);
	rookPoints[0][6] = cv::Point(3 * WINDOW_WIDTH / 4, WINDOW_WIDTH / 8);
	rookPoints[0][7] = cv::Point(26 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 8);
	rookPoints[0][8] = cv::Point(26 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 4);
	rookPoints[0][9] = cv::Point(22 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 4);
	rookPoints[0][10] = cv::Point(22 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 8);
	rookPoints[0][11] = cv::Point(18 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 8);
	rookPoints[0][12] = cv::Point(18 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 4);
	rookPoints[0][13] = cv::Point(14 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 4);
	rookPoints[0][14] = cv::Point(14 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 8);
	rookPoints[0][15] = cv::Point(WINDOW_WIDTH / 4, WINDOW_WIDTH / 8);
	rookPoints[0][16] = cv::Point(WINDOW_WIDTH / 4, 3 * WINDOW_WIDTH / 8);
	rookPoints[0][17] = cv::Point(13 * WINDOW_WIDTH / 32, 3 * WINDOW_WIDTH / 8);
	rookPoints[0][18] = cv::Point(5 * WINDOW_WIDTH / 16, 13 * WINDOW_WIDTH / 16);
	rookPoints[0][19] = cv::Point(WINDOW_WIDTH / 4, 13 * WINDOW_WIDTH / 16);

	const cv::Point* ppt[1] = { rookPoints[0] };
	int npt[] = { 20 };
	cv::fillPoly(img,
		ppt,
		npt,
		1,
		cv::Scalar(255, 255, 255),
		lineType);

}

void DrawLine(cv::Mat img, cv::Point start, cv::Point end) {
	int thickness = 2;
	int lineType = 8;
	cv::line(img,
		start,
		end,
		cv::Scalar(0, 0, 0),
		thickness,
		lineType);
}


int main()
{
	std::cout << "start..." << std::endl;

	cv::Mat atomImage = cv::Mat::zeros(WINDOW_WIDTH, WINDOW_WIDTH, CV_8UC3);
	cv::Mat rookImage = cv::Mat::zeros(WINDOW_WIDTH, WINDOW_WIDTH, CV_8UC3);
	
	DrawEllipse(atomImage, 90);
	DrawEllipse(atomImage, 0);
	DrawEllipse(atomImage, 45);
	DrawEllipse(atomImage, -45);

	DrawFilledCircle(atomImage, cv::Point(WINDOW_WIDTH / 2, WINDOW_WIDTH / 2));
	
	DrawPolygon(rookImage);

	cv::rectangle(rookImage,
		cv::Point(0, 7 * WINDOW_WIDTH / 8),
		cv::Point(WINDOW_WIDTH, WINDOW_WIDTH),
		cv::Scalar(0, 255, 255),
		-1,
		8);
	DrawLine(rookImage, cv::Point(0, 15 * WINDOW_WIDTH / 16),
		cv::Point(WINDOW_WIDTH, 15 * WINDOW_WIDTH / 16));

	cv::imshow(WINDOW_NAME1, atomImage);
	cv::moveWindow(WINDOW_NAME1, 0, 200);
	cv::imshow(WIN                              DOE_NAME2, rookImage);
	cv::moveWindow(WINDOE_NAME2, WINDOW_WIDTH, 200);

	cv::waitKey();
	
	std::cout << "end." << std::endl;
	return 0;
}

```

