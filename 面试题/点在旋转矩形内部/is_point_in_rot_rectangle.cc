/*---------------------------------------
题目： 判断二维空间中任意一点是否在旋转矩形内部
已知条件：旋转矩形中心center(x,y), 旋转矩形的长l 和 宽w， 以及与X轴旋转角度theta
返回值： 是否在其内部
---------------------------------------*/
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <Eigen/Dense>
#include <math.h>       /* cos */
#include <iostream>

#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/common/transforms.h> // pcl::transformPointCloud

#define PI 3.14159265

// 点坐标
struct Point {
  Point(const double& x, const double& y):x(x), y(y){};
  double x;
  double y;
};

// 向量
struct Vector2d{
  Vector2d(const double& x, const double& y):x(x), y(y){};
  double x;
  double y;
};

// 计算三角形面积
double CalculateTriangleArea(const Point& a, const Point& b, const Point& c){
    // 向量叉乘x1y2-x2y1
    double res = 0;
    if((a.x == b.x && a.y == b.y )|| (a.x == c.x && a.y == c.y )|| (b.x == c.x && b.y == c.y)) return res;
    Vector2d ba(a.x -b.x, a.y - b.y);
    Vector2d bc(c.x -b.x, c.y - b.y);
    res = fabs(ba.x*bc.y - bc.x*ba.y) * 0.5;
    return res;
}

// 绘制箭头
void DrawArrow(cv::Mat &img, cv::Point pStart, cv::Point pEnd, int len,
               int alpha, cv::Scalar &color, int thickness, int lineType) {
  cv::Point arrow;

  double angle =
      atan2((double)(pStart.y - pEnd.y), (double)(pStart.x - pEnd.x));
  cv::line(img, pStart, pEnd, color, thickness, lineType);

  arrow.x = pEnd.x + len * cos(angle + PI * alpha / 180);
  arrow.y = pEnd.y + len * sin(angle + PI * alpha / 180);
  cv::line(img, pEnd, arrow, color, thickness, lineType);
  arrow.x = pEnd.x + len * cos(angle - PI * alpha / 180);
  arrow.y = pEnd.y + len * sin(angle - PI * alpha / 180);
  cv::line(img, pEnd, arrow, color, thickness, lineType);
}


// Debug: 绘制旋转矩形和待测试点
void DrawRotateRectangle(const pcl::PointCloud<pcl::PointXYZ>& cloud, const Point& p){
    int img_x = 200, img_y = 200;
    cv::Scalar arrow_color = cv::Scalar(0, 0, 0);
    cv::Mat img(img_y, img_x, CV_8UC3, cv::Scalar(255, 255, 255));
    DrawArrow(img, cv::Point(img_x/2.0, img_y -20),
            cv::Point(img_x/2.0, 20), 6, 45, arrow_color, 2, 8);
    DrawArrow(img, cv::Point(20, img_y/2.0),
            cv::Point(img_x-20, img_y/2.0), 6, 45, arrow_color, 2, 8);
    for(int i=0; i<4; ++i){
      if(i < 3){
        cv::line(img, cv::Point(cloud.points[i].x+100, -cloud.points[i].y+100), cv::Point(cloud.points[i+1].x+100, -cloud.points[i+1].y+100), arrow_color, 2, 8);
      }else{
        cv::line(img, cv::Point(cloud.points[i].x+100, -cloud.points[i].y+100), cv::Point(cloud.points[0].x+100, -cloud.points[0].y+100), arrow_color, 2, 8);
      }
    }
    cv::circle(img, cv::Point(p.x+100, -p.y+100), 2, arrow_color, 2, 8);
    cv::imshow("rotate_rectangle", img);
    cv::waitKey(0);
}



bool IsPointInRotateRectangle(const Point& center, const double& w, const double& h, const double& theta, const Point& p)
{
    // 还原4个角点坐标
    pcl::PointCloud<pcl::PointXYZ> cloud;
    cloud.points.emplace_back(pcl::PointXYZ(-w/2.0, h/2.0, 0));
    cloud.points.emplace_back(pcl::PointXYZ(-w/2.0, -h/2.0, 0));
    cloud.points.emplace_back(pcl::PointXYZ(w/2.0, -h/2.0, 0));
    cloud.points.emplace_back(pcl::PointXYZ(w/2.0, h/2.0, 0));

    // DrawRotateRectangle(cloud, p);
    Eigen::Matrix4d mat = Eigen::Matrix4d::Identity();
    mat << cos(theta*PI/ 180.0), -sin(theta*PI/ 180.0), 0, center.x,
           sin(theta*PI/ 180.0), cos(theta*PI/ 180.0),  0, center.y,
           0,                    0,                     1, 0,
           0,                    0,                     0, 1 ;
    std::cout << "mat: " << mat << std::endl;
    pcl::transformPointCloud(cloud, cloud, mat);
    // TODO: debug, 查看点与矩形位置
    // DrawRotateRectangle(cloud, p);

    // 旋转矩形4个角点ABCD
    Point A(cloud.points[0].x, cloud.points[0].y);
    Point B(cloud.points[1].x, cloud.points[1].y);
    Point C(cloud.points[2].x, cloud.points[2].y);
    Point D(cloud.points[3].x, cloud.points[3].y);

    // 法一： 面积法
    // auto area1 = CalculateTriangleArea(A, B, p);
    // auto area2 = CalculateTriangleArea(B, C, p);
    // auto area3 = CalculateTriangleArea(C, D, p);
    // auto area4 = CalculateTriangleArea(D, A, p);
    // std::cout << "area1: " << area1 << ", area2: " << area2 << ", area3: " << area3 << ", area4: " << area4 << std::endl;
    // if(fabs(area1+area2+area3+area4 - w*h)< 1e-3) return true;
    // else return false;

    // 法二： 向量方向性, 满足(BA*Bp)(DC*Dp)>=0，先叉乘再点乘
    Vector2d BA(A.x -B.x, A.y - B.y);
    Vector2d Bp(p.x -B.x, p.y - B.y);
    Vector2d DC(C.x -D.x, C.y - D.y);
    Vector2d Dp(p.x -D.x, p.y - D.y);
    /* 若严格按照ABCD顺序来，两个数都是大于0，乘积的方式是顾忌到矩形4个顶点的ABCD顺时针排序还是逆时针排序 */
    auto val1 = (BA.x * Bp.y - Bp.x * BA.y) * (DC.x * Dp.y - Dp.x * DC.y);
    Vector2d DA(D.x -A.x, D.y - A.y);
    Vector2d BC(B.x -C.x, B.y - C.y);
    auto val2 = (DA.x * Dp.y - Dp.x * DA.y)* (BC.x * Bp.y - Bp.x * BC.y);
    if(val1 >=0 && val2 >=0) return true;
    else return false;
}



int main(){
    // test
    Point p(20, 50), center(20, 40);
    double length = 80.0, width = 40.0, theta = 60;
    auto res = IsPointInRotateRectangle(center, length, width, theta, p);
    std::cout << "res: " << res << std::endl;
    return 0;
}