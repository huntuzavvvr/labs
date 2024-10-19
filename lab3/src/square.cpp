#include "../include/square.h"
#include <iostream>
#include <cmath>
#include <vector>

Square::operator double(){
    double a = Point::find_len(points[0].x_point, points[1].x_point, points[0].y_point, points[1].y_point);
    double b = Point::find_len(points[1].x_point, points[2].x_point, points[1].y_point, points[2].y_point);
    return a * b;
}

Point Square::find_center(){
    double x_center = (this->points[0].x_point + this->points[2].x_point) / 2;
    double y_center = (this->points[0].y_point + this->points[2].y_point) / 2;
    return Point(x_center, y_center);
}

double Square::dot_product (const Point& p1, const Point& p2, const Point& p3){
    Point v1 = {p2.x_point - p1.x_point, p2.y_point - p1.y_point};
    Point v2 = {p3.x_point - p2.x_point, p3.y_point - p2.y_point};
    return v1.x_point * v2.x_point + v1.y_point * v2.y_point;
}

std::istream& operator>>(std::istream& ist, Square& Square){
    std::cout << "Введите координаты левого верхнего угла и длину стороны\n";
    double x, y, len;
    ist >> x >> y;
    Point p1(x, y);
    ist >> len;
    Point p2(p1.x_point + len, p1.y_point);
    Point p3(p1.x_point + len, p1.y_point - len);
    Point p4(p1.x_point, p1.y_point - len);
    Square.points.push_back(p1);
    Square.points.push_back(p2);
    Square.points.push_back(p3);
    Square.points.push_back(p4);
    return ist;
}