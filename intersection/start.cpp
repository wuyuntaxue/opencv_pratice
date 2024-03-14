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
    int c1 = (j1.x - k1.x) * (k2.y - k1.y) - (k2.x - k1.x) * (j1.y - k1.y);
    int c2 = (j2.x - k1.x) * (k2.y - k1.y) - (k2.x - k1.x) * (j2.y - k1.y);
    std::cout << "c1: " << c1 << ", c2: " << c2 << std::endl;
    if ((c1 ^ c2) > 0) {
        std::cout << "同号，即j1、j2在线段k的同一侧" << std::endl;
        return false;
    }
    // 这里=0也认为相交，因为平行但在坐标轴上没有投影的情况已经在上一步被排除了

    // j1->k1、j1->k2与分别差乘j1->j2
    int d1 = (k1.x - j1.x) * (j2.y - j1.y) - (j2.x - j1.x) * (k1.y - j1.y);
    int d2 = (k2.x - j1.x) * (j2.y - j1.y) - (j2.x - j1.x) * (k2.y - j1.y);
    std::cout << "d1: " << d1 << ", d2: " << d2 << std::endl;
    if ((d1 ^ d2) > 0) {
        std::cout << "同号，即k1、k2在线段j的同一侧" << std::endl;
        return false;
    }

    /*
    设矢量 P = (x1, y1)，Q = ( x2, y2 )，则矢量叉积定义为：P × Q = x1*y2 - x2*y1，其结果是一个矢量，与为 P Q
向量所在平面的法向量。显然有性质 P × Q = - ( Q × P ) 和 P × ( - Q ) = - ( P × Q )。
叉积的一个非常重要性质是可以通过它的符号判断两矢量相互之间的顺逆时针关系：
　　若 P × Q > 0 , 则 P 在 Q 的顺时针方向。
　　若 P × Q < 0 , 则 P 在 Q 的逆时针方向。
　　若 P × Q = 0 , 则 P 与 Q 共线，但可能同向也可能反向。
    */

    // 线段相交
    return true;
}

// 判断点a是否在多边形poly内
bool test_inPolygon(const cv::Point A, const std::vector<cv::Point> &poly) {
    /*
    1. 经过点A做一条与x轴的平行线，记作直线a
    2. 遍历多边形的每一条边，判断与直线a交点坐标的x在点A的左/右侧
    3. 分别记录在点A左侧、右侧的交点个数。如果都是奇数，则点A在多边形内；否则在多边形外
    */

    /*
    记直线为： Y = kX + b；已知直线上两点的坐标A、B
    k = (A.y-B.y)/(A.x-B.x);
    b = A.y - (k * A.x);

    X = (Y - b)/k;
    */

    unsigned int leftCount = 0, rightCount = 0;

    for (int i = 0, j = poly.size() - 1; i < poly.size(); i++) {
        if (std::max(poly.at(i).y, poly.at(j).y) > A.y && std::min(poly.at(i).y, poly.at(j).y) <= A.y) {
            // 当前边和经过点A与x轴的平行线有交点

            double k = 0.0;
            if ((poly.at(i).x != poly.at(j).x)) {
                k = (poly.at(i).y - poly.at(j).y) / (poly.at(i).x - poly.at(j).x);
            }
            double b = poly.at(i).y - (k * poly.at(i).x);
            std::cout << "k: " << k << ", b: " << b << std::endl;

            double interX = 0.0;
            if (abs(k) <= 1e-15) { // 浮点型不能之间判断是否等于0
                interX = poly.at(i).x;
            } else {
                interX = (A.y - b) / k;
            }

            if (interX < A.x) {
                leftCount++;
            } else if (interX > A.x) {
                rightCount++;
            }
        }
        j = i;
    }

    std::cout << "leftCount: " << leftCount << ", rightCount: " << rightCount << std::endl;
    if ((leftCount & 0x01) == 0x01 && (rightCount & 0x01) == 0x01) {
        return true;
    }

    return false;
}


int main() {
    {
        cv::Point p(5, 5);
        cv::Rect  r(0, 10, 10, 10);

        auto res = test_pointInRect(p, r);
        std::cout << "res: " << res << std::endl;
    }

    {
        cv::Point j1(2, 2);
        cv::Point j2(4, 4);
        cv::Point k1(0, 0);
        cv::Point k2(2, 2);

        if (test_intersection(j1, j2, k1, k2)) {
            std::cout << "两线段相交" << std::endl;
        }
    }

    {
        std::vector<cv::Point> poly;
        poly.emplace_back(cv::Point(1, 0));
        poly.emplace_back(cv::Point(2, 1));
        poly.emplace_back(cv::Point(1, 2));
        poly.emplace_back(cv::Point(0, 1));

        cv::Point pointA(1, 1);

        if (test_inPolygon(pointA, poly)) {
            std::cout << "点在多边形内" << std::endl;
        }
    }

    return 0;
}
