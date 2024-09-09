#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <string>
#include <vector>


void test_read_write(std::string filename) {
    cv::Mat     image    = cv::imread(filename, cv::IMREAD_UNCHANGED);

    cv::cvtColor(image, image, cv::COLOR_BGR2GRAY);

    cv::imshow("test", image);

    cv::waitKey();

    std::string savename = "save.png";
    if (cv::imwrite(savename, image)) {
        std::cout << "save image success" << std::endl;
    }
}

void read_write_image(std::string filename) {
    cv::Mat M = cv::imread(filename, cv::IMREAD_COLOR); // 将图片读如Mat中
    // Mat为图像矩阵

    // 判断文件是否正常打开
    if (M.empty()) {
        std::cerr << "Can not load image " << filename << std::endl;
        cv::waitKey(1000); // 等待1000 ms后退出程序
        return;
    }

    cv::putText(M, "hello", cv::Point(200, 270), cv::FONT_HERSHEY_SIMPLEX, 3, cv::Scalar(255, 255, 255), 4,
                8); // 在图像上显示文字

    cv::circle(M, cv::Point(100, 100), 100, cv::Scalar(25, 0, 255), 3, 8); // 在图像上画圆形

    cv::line(M, cv::Point(100, 100), cv::Point(200, 200), cv::Scalar(255, 0, 55), 2, 8); // 在图像上画线

    cv::rectangle(M, cv::Point(100, 100), cv::Point(200, 200), cv::Scalar(0, 255, 5), 8); // 在图像上画矩形

    cv::ellipse(M, cv::Point(200, 200), cv::Size(150, 200), -45, 0, 360, cv::Scalar(200, 200, 200), 3,
                8); // 在图像上画椭圆

    // cv::imshow("原图", M); // 显示图片
    // cv::waitKey();

    cv::Mat dstImage;
    cv::blur(M, dstImage, cv::Size(10, 10)); // 模糊
    cv::imshow("blur", dstImage);
    cv::waitKey();

    // cv::Mat dst;

    // cv::resize(M, dst, cv::Size(300, 300)); // 修改图片大小
    // cv::imshow("resize", dst);              // 显示图片
    // cv::waitKey();

    cv::imwrite("out.jpg", dstImage); // 将图片数据输出
}

void mat_test() {
    cv::Mat imat;               // Mat对象可以表示图像矩阵
    imat.create(4, 4, CV_8UC2); // 申请空间，4行4列，(每个像素是8*2位？)，没有给初值
    std::cout << "M = " << std::endl << " " << imat << std::endl << std::endl;

    cv::Mat m2(2, 2, CV_8UC3, cv::Scalar(0, 0, 255)); // 2行2列，(每个像素是8*3位？)，给定全体像素的值
    std::cout << "M = " << std::endl << " " << m2 << std::endl << std::endl;
    std::cout << m2.rows << std::endl;

    // 3维图像
    int sz[3] = {3, 3, 3}; // 构造3维矩阵时，需先定义一个数组，说明每个维度的尺寸，这里表示每个维度尺寸都是3
    cv::Mat m3(3, sz, CV_8UC1, cv::Scalar::all(0));
    std::cout << m3.rows << std::endl;
}

void point_test() {

    // Point表示二维坐标系的一个点，坐标用该对象的x,y元素表示
    cv::Point p1(6, 6);  // 初始化坐标
    std::cout << "Point default: " << p1 << std::endl;

    p1.x = 1;
    p1.y = 2;

    std::cout << "Point options: " << p1 << std::endl;
}

int main(int argc, char *argv[]) {
    // if (argc < 2) {
    //     std::cout << "param" << std::endl;
    //     return 0;
    // }
    // read_write_image(argv[1]);

    // mat_test();
    point_test();


    return 0;
}


// https://blog.csdn.net/JavaYoung123/article/details/106752838
