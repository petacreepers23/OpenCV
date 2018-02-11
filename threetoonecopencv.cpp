#include "opencv2/highgui/highgui.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2\objdetect\objdetect.hpp>
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

int main() {
	int i = 0;
	cout << "3 to 1 (0)   or   1 to 3 (1):>> ";
	cin >> i;
	if(i==0){
		Mat r = imread("r.jpg", CV_LOAD_IMAGE_GRAYSCALE);
		if (!r.data) {
			cout << "Could not open or find the image r" << endl;
			return 1;
		}
		Mat g = imread("g.jpg", CV_LOAD_IMAGE_GRAYSCALE);
		if (!r.data) {
			cout << "Could not open or find the image g" << endl;
			return 2;
		}
		Mat b = imread("b.jpg", CV_LOAD_IMAGE_GRAYSCALE);
		if (!r.data) {
			cout << "Could not open or find the image b" << endl;
			return 3;
		}
		if (r.size != g.size || g.size != b.size) {
			cout << "Images have different sizes" << endl;
			return 3;
		}
		vector<Mat> images(3);
		Mat image = Mat::zeros(r.rows, g.cols, CV_8UC3);
		images.at(0) = b;
		images.at(1) = g;
		images.at(2) = r;
		Mat colorImage;
		merge(images, colorImage);
		imwrite("color.jpg", colorImage);
		imshow("Final", colorImage);
		waitKey(0);
	}
	else {
		Mat original = imread("color.jpg", CV_LOAD_IMAGE_COLOR);
		if (!original.data) {
			cout << "Could not open or find the image color" << endl;
			return 4;
		}
		Mat splitChannels[3];
		split(original, splitChannels);
		imwrite("blue.jpg", splitChannels[0]);
		imwrite("green.jpg", splitChannels[1]);
		imwrite("red.jpg", splitChannels[2]);
		imshow("blue.jpg", splitChannels[0]);
		imshow("green.jpg", splitChannels[1]);
		imshow("red.jpg", splitChannels[2]);
		waitKey(0);
	}
	return 0;
}