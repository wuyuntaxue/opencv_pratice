#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <string>
#include <vector>

// 点是否在矩形内
bool test_pointInRect(const cv::Point p, const cv::Rect r) {
    if (p.x >= r.x && p.x <= r.x + r.width) {
        if (p.y <= r.y && p.y >= r.y - r.height) {
            return true;
        }
    }
    return false;
}

// 判断两个线段是否相交
// j1和j2为线段j的端点；k1和k2为线段k的端点
bool test_intersection(cv::Point j1, cv::Point j2, cv::Point k1, cv::Point k2) {
    // 判断两条线段在x/y轴上的投影是否有重合，如果没有重合，则必然不相交，就不用进行之后的运算

    // j和k在x轴上的投影
    int jxMax = std::max(j1.x, j2.x);
    int jxMin = std::min(j1.x, j2.x);
    int kxMax = std::max(k1.x, k2.x);
    int kxMin = std::min(k1.x, k2.x);
    if (jxMax < kxMin || kxMax < jxMin) {
        std::cout << "x轴投影不重合" << std::endl;
        return false;
    }

    int jyMax = std::max(j1.y, j2.y);
    int jyMin = std::min(j1.y, j2.y);
    int kyMax = std::max(k1.y, k2.y);
    int kyMin = std::min(k1.y, k2.y);
    if (jyMax < kyMin || kyMax < jyMin) {
        std::cout << "y轴投影不重合" << std::endl;
        return false;
    }


    // 向量差乘
    // 如果线段j和k相交，
    // 则以k1为顶点，向量k1->j1、k1->j2与k1->k2的乘积应该是异号的，这样保证点j1、j2在线段k的两端
    // 同理，也需要证明k1、k2在线段j的两端
    int c1 = (j1.x - k1.x)*(k2.y - k1.y) - (k2.x - k1.x)*(j1.y - k1.y);
    int c2 = (j2.x - k1.x)*(k2.y - k1.y) - (k2.x - k1.x)*(j2.y - k1.y);
    std::cout << "c1: " << c1 << ", c2: " << c2 << std::endl;
    if ((c1 ^ c2) > 0) {
        std::cout << "同号，即j1、j2在线段k的同一侧" << std::endl;
        return false;
    }
    // 这里=0也认为相交，因为平行但在坐标轴上没有投影的情况已经在上一步被排除了

    // j1->k1、j1->k2与分别差乘j1->j2
    int d1 = (k1.x - j1.x)*(j2.y - j1.y) - (j2.x - j1.x)*(k1.y - j1.y);
    int d2 = (k2.x - j1.x)*(j2.y - j1.y) - (j2.x - j1.x)*(k2.y - j1.y);
    std::cout << "d1: " << d1 << ", d2: " << d2 << std::endl;
    if ((d1 ^ d2) > 0) {
        std::cout << "同号，即k1、k2在线段j的同一侧" << std::endl;
        return false;
    }

    /*
    设矢量 P = (x1, y1)，Q = ( x2, y2 )，则矢量叉积定义为：P × Q = x1*y2 - x2*y1，其结果是一个矢量，与为 P Q 向量所在平面的法向量。显然有性质 P × Q = - ( Q × P ) 和 P × ( - Q ) = - ( P × Q )。 
叉积的一个非常重要性质是可以通过它的符号判断两矢量相互之间的顺逆时针关系： 
　　若 P × Q > 0 , 则 P 在 Q 的顺时针方向。 
　　若 P × Q < 0 , 则 P 在 Q 的逆时针方向。 
　　若 P × Q = 0 , 则 P 与 Q 共线，但可能同向也可能反向。
    */

   // 线段相交
    return true;
}

int main() {
    // cv::Point p(5, 5);
    // cv::Rect  r(0, 10, 10, 10);

    // auto res = test_pointInRect(p, r);
    // std::cout << "res: " << res << std::endl;

    cv::Point j1(0, 2);
    cv::Point j2(2, 0);
    cv::Point k1(0, 0);
    cv::Point k2(2, 2);

    if (test_intersection(j1, j2, k1, k2)) {
        std::cout << "两线段相交" << std::endl;
    }
    return 0;
}
