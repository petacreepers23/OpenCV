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
	int ammount = 42;
	for (int i = 0; i < ammount; i++) {
		string name, r, g, b;
		if (i < 10) {
			//Sorry...
			name = "orig/0" + to_string(i) + ".bmp";
			r = "red/0" + to_string(i) + ".bmp";
			g = "green/0" + to_string(i) + ".bmp";
			b = "blue/0" + to_string(i) + ".bmp";
		}
		else {
			name = "orig/" + to_string(i) + ".bmp";
			r = "red/" + to_string(i) + ".bmp";
			g = "green/" + to_string(i) + ".bmp";
			b = "blue/" + to_string(i) + ".bmp";
		}
		Mat original = imread(name, CV_LOAD_IMAGE_GRAYSCALE);
		if (!original.data) {
			cout << "Could not open or find the image color" << endl;
			return 4;
		}
		vector<Mat> images(3);
		//BLUE
		Mat cero = Mat::zeros(original.rows, original.cols, CV_8UC1);
		images.at(0) = original;
		images.at(1) = cero;
		images.at(2) = cero;
		Mat blue,green,red;
		merge(images, blue);
		imwrite(b, blue);
		//GREEN
		images.at(0) = cero;
		images.at(1) = original;
		images.at(2) = cero;
		merge(images, green);
		imwrite(g, green);
		//RED
		images.at(0) = cero;
		images.at(1) = cero;
		images.at(2) = original;
		merge(images, blue);
		imwrite(r, red);
	}
	return 0;
}
