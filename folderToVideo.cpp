#include <iostream>                     // for standard I/O
#include <opencv2/core.hpp>             // Basic OpenCV structures (cv::Mat)
#include <opencv2/videoio.hpp>          // Video write
#include <opencv2/highgui.hpp>          // imread
#include <string>                       // for strings
#include <sstream>                      // for real strings
#include <filesystem>      // directory_iterator

namespace fs = std::filesystem;
using namespace cv;

struct RunOnce {
    template<typename T> RunOnce(T&& f) { f(); }
};

//Send a folder path as an argument, and each file will be appended into a video.
int main(int argc, char** path) {
    if (argc < 2) {
        return -1;
    }

    VideoWriter outputVideo;
    std::stringstream name;;
    name << path[1] << "video.avi";

    for (auto& p : fs::directory_iterator(path[1])) {
        Mat m = imread(p.path().string());
        static RunOnce a([&](){outputVideo.open(name.str(), VideoWriter::fourcc('M', 'J', 'P', 'G'), 60, m.size()); });
        outputVideo << m;
    }

    outputVideo.release();
    
    return 0;
}
