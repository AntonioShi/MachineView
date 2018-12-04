//
// Created by stardust on 18-12-3.
//

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>
#include <string>
#include <opencv2/imgproc.hpp>

using namespace std ;
using namespace cv ;

int main(int argc, char** argv){

    String imageName = ("lab4/images/sample1.png") ;//path

    if (argc > 1){
        imageName = argv[1] ;
    }

    Mat image ;//image mat
    image = imread(imageName, IMREAD_COLOR) ;//read

    if (image.empty()){
        cout << "could not open the image which you're finding" << endl ;
        return  -1 ;
    }
    namedWindow( "Display window", WINDOW_AUTOSIZE ); // Create a window for display.
    imshow("Display window", image) ;

    cout << image.type() ;//16

    //deal with this image

    Mat grayImage ;
    Mat binImage ;

    cvtColor(image, grayImage, COLOR_BGRA2GRAY) ; //转换为灰度图并平滑滤波

    namedWindow( "Display window", WINDOW_AUTOSIZE ); // Create a window for display.
    imshow("gray", grayImage) ;

    threshold(grayImage, binImage, 145, 255, CV_THRESH_BINARY) ;

    namedWindow( "Display window", WINDOW_AUTOSIZE ); // Create a window for display.
    imshow("binary", binImage) ;


   //定义变量
   vector<vector<Point>> contours ;
   vector<Vec4i>hierarchy ;

   grayImage = grayImage > 100 ;//?
   findContours(grayImage, contours, hierarchy, RETR_TREE, CV_CHAIN_APPROX_SIMPLE) ;//can shu
   //RETR_TREE:提取所有轮廓并重新建立网状轮廓结构


    //绘制轮廓图
    Mat dstImage = Mat::zeros(grayImage.size(), CV_8UC3);
    for (int i = 0; i < hierarchy.size(); i++) {
        Scalar color = Scalar(rand() % 255, rand() % 255, rand() % 255);
        drawContours(dstImage, contours, i, color, CV_FILLED, 8, hierarchy);
    }
    imshow("轮廓图", dstImage);//


    waitKey(0); // Wait for a keystroke in the window

    return 0 ;
}

