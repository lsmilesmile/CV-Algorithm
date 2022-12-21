# PS魔法棒

> Felix
>
> 2022.12.21



```c++
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>

const cv::Point SEED(30, 30);
const int GRAY_THRESHOLD = 10;

struct Queue {
	int x;
	int y;
	Queue* next;
};
void fun(const cv::Mat& src, cv::Mat& dst);

int main() {
	cv::Mat src = cv::imread("./imgs/1.jpg");
	cv::imshow("src", src);
	cv::Mat gray;
	cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);
	cv::imshow("gray", gray);


	cv::Mat dst = src.clone();
	fun(gray, dst);
	cv::imshow("dst", dst);
	cv::waitKey();
	

	system("pause");
	return 0;
}

void fun(const cv::Mat& src, cv::Mat& dst) {
	if (src.channels() != 1)
		return;
	int width = src.cols;
	int height = src.rows;
	cv::Mat M = cv::Mat::zeros(src.size(), CV_8UC1);
	M.at<uchar>(SEED.y, SEED.x) = 1;

	int start = 0;
	int end = 1;
	Queue *queue = new Queue;
	queue->x = SEED.x;
	queue->y = SEED.y;
	queue->next = NULL;

	Queue *first = queue;
	Queue *last = queue;
	uchar pixel = src.at<uchar>(SEED.y, SEED.x);
	while (end - start > 0) {
		int x = first->x;
		int y = first->y;

		for (int yy = -1; yy <= 1; yy++) {
			for (int xx = -1; xx <= 1; xx++) {
				int cx = x + xx;
				int cy = y + yy;
				if (cx >= 0 && cx < width && cy >= 0 && cy < height) {
					if (abs(src.at<uchar>(cy, cx) - pixel) <= GRAY_THRESHOLD
						&& M.at<uchar>(cy, cx) != 1) {
						Queue *node = new Queue;
						node->x = cx;
						node->y = cy;
						node->next = NULL;
						end++;
						last->next = node;
						last = node;
						M.at<uchar>(cy, cx) = 1;
					}
				}
			}
		}
		Queue *temp = first;
		first = first->next;
		delete temp;
		start++;
	}
	for (int i = 0; i < src.rows; i++) {
		for (int j = 0; j < src.cols; j++) {
			if ((int)M.at<uchar>(i, j) == 1) {
				dst.at<cv::Vec3b>(i, j)[0] = 0;
				dst.at<cv::Vec3b>(i, j)[1] = 255;
				dst.at<cv::Vec3b>(i, j)[2] = 0;
			}
		}
	}
}

```

