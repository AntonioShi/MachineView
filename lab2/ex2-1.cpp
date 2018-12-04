#include <iostream>
#include <opencv2/opencv.hpp>
#include <sys/time.h>

using namespace std;
using namespace cv;

int main() {
    VideoCapture capture(0);
    Mat edges;
    while (1) {
        Mat frame;
        int x , y;
        time_t time1;
        struct tm *lm;
        capture >> frame;
        if (frame.empty()) {
            cout << "no frame" << endl;
            break;
        } else {
            time(&time1);
            lm = localtime(&time1);
            x = frame.cols / 2;
            y = frame.rows / 2;
            cvtColor(frame, edges, CV_BGR2GRAY);
//            GaussianBlur(edges, edges, Size(3, 3), 0);
//            Canny(edges, edges, 70, 150);
            line(frame, Point(x-10, y), Point(x+10, y), Scalar(0, 0, 255), 2);
            line(frame, Point(x, y-10), Point(x, y+10), Scalar(0, 0, 255), 2);
            circle(frame, Point(x, y), 10, Scalar(255, 0, 0), 2);
            putText(frame, asctime(lm), Point(x, y+20), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0));
            imshow("edges", edges);
            imshow("frame", frame);
        }
        waitKey(30);
    }
    return 0;
}

