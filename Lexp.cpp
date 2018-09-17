#include <iostream>
#include <opencv2\core.hpp>
#include <opencv2\highgui.hpp>
#include <iomanip>
#include <string>
#include <iostream>
#include <experimental/filesystem>


namespace fs = std::experimental::filesystem;
using namespace std;
using namespace cv;

struct RunOnce {
	template<typename T> RunOnce(T &&f) { f(); }
};

int main() {
	Mat current, result, dst;
	unsigned int i = 1;
	bool frames = !false;
	if (frames) {
		std::string path = "ss";
		for (auto & p : fs::directory_iterator(path)) {
			static RunOnce a([&]() {stringstream ss; ss << p; result = imread(ss.str()); });
			double val = 1.0 / (i);
			stringstream ss; ss << p;
			cout << p << endl;
			current = imread(ss.str());
			addWeighted(current, val, result, 1 - val, 0, result);
			imshow("lol", result);
			waitKey(60);
			i++;
		}
	}
	else {
		VideoCapture cap("video.avi");
		if (!cap.isOpened())
			return -1;
		while (cap.read(current)) {
			static RunOnce a([&]() {current.copyTo(result); });
			double val = 1.0 / (i);
			addWeighted(current, val, result, 1 - val, 0, result);
			imshow("lol", result);
			waitKey(60);
			i++;
		}
	}
	imwrite("resultado.jpg", result);
	waitKey(0);
}
