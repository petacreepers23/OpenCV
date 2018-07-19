#include <opencv2\core.hpp>
#include <opencv2\highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char* argv[]) {
	int size = 7;//only odd
	int max_step = (size - 1) / 2;
	Mat m = imread(argv[1]);
	for (int i = max_step; i < m.rows- max_step; i+=size) {
		for (int j = max_step; j < m.cols- max_step; j+=size) {
			Vec3b colour = m.at<Vec3b>(Point(j, i));//Mask
			colour[0] = colour[0] / 64 * 64 + 32;
			colour[1] = colour[1] / 64 * 64 + 32;
			colour[2] = colour[2] / 64 * 64 + 32;
			for (int k = -max_step; k <= max_step; k++) {
				for (int l = -max_step; l <= max_step; l++) {
					m.at<Vec3b>(Point(j - k, i - l)) = colour;
				}
			}
		}
	}
	m = m(Rect(Point(0, 0), Point(m.cols - m.cols%size, m.rows - m.rows%size)));
	try {
		imshow("pixeled", m);
		waitKey(0);
	} catch (exception e) {
		cout << "ERROR! " << e.what();
		getchar();
		return 1;
	}
	stringstream s;
	s << argv[1] << "_pixeled.jpg";
	imwrite(s.str(), m);
	return 0;
}
