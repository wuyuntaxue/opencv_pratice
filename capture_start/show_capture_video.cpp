/*
调用系统默认摄像头，并显示
*/
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>



int main()
{
    cv::VideoCapture cap(0);
    for (;;)
    {
        cv::Mat frame;
        cap.read(frame);
        cv::imshow("摄像头0-视频", frame);
        cv::waitKey(10);
    }
    return 0;
}
