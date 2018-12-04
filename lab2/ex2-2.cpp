#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
#define SIZE 4

vector<Point2f> src1_points;
vector<Point2f> src2_points;
int click_counts = 0;
Mat src1, src2, dst, dst2, matrix;

void rect(int event, int x, int y, int flags, void *);

int main() {
    src1 = imread("../ex2/images/lena.png");
    src2 = imread("../ex2/images/adv.png");
    if (src1.empty() || src2.empty()) {
        cout << "can not load the image!" << endl;
        return -1;
    }
    src1_points.emplace_back(Point2f(0, 0));
    src1_points.emplace_back(Point2f(src1.cols - 1, 0));
    src1_points.emplace_back(Point2f(src1.cols - 1, src1.rows - 1));
    src1_points.emplace_back(Point2f(0, src1.rows - 1));

    dst2 = src2.clone();

    imshow("src1", src1);
    imshow("src2", src2);
    namedWindow("dst2", CV_WINDOW_AUTOSIZE);
    imshow("dst2", dst2);
    setMouseCallback("dst2", rect);
    waitKey(0);
    return 0;

}

void rect(int event, int x, int y, int flags, void *) {
    if (click_counts == SIZE) {
        dst = Mat::zeros(src2.size(), src2.type());
        // 寻找由lena图转变为广告牌大小的变换矩阵
        matrix = findHomography(src1_points, src2_points);
        //  透视投影
        warpPerspective(src1, dst, matrix, src2.size());

        // 将广告牌区域填充为黑色
        Mat temp = src2.clone();
        Point points[SIZE];
        for(int i = 0; i < SIZE; i++) {
            points[i] = src2_points[i];
        }
        fillConvexPoly(temp, points, 4, Scalar(0, 0, 0));
        dst2 = dst + temp;
        imshow("dst2", dst2);
    }
    if (event == CV_EVENT_LBUTTONDOWN) {
        src2_points.emplace_back(Point2f(x, y));
        click_counts++;
        circle(dst2, Point2f(x, y), 2, Scalar(0, 0, 255), -1);
        imshow("dst2", dst2);
    }
}

