#include "../include/triangle.h"
#include <iostream>
#include <cmath>
#include <vector>

Triangle::operator double(){
    double a = Point::find_len(points[0].x_point, points[1].x_point, points[0].y_point, points[1].y_point);
    double b = Point::find_len(points[1].x_point, points[2].x_point, points[1].y_point, points[2].y_point);
    double c = Point::find_len(points[2].x_point, points[0].x_point, points[2].y_point, points[0].y_point);
    double p = (a + b + c) / 2;
    return std::sqrt(p * (p - a) * (p - b) * (p - c));
}

Point Triangle::find_center(){
    double x_center = (this->points[0].x_point + this->points[1].x_point + this->points[2].x_point) / 3;
    double y_center = (this->points[0].y_point + this->points[1].y_point + this->points[2].y_point) / 3;
    return Point(x_center, y_center);
}

std::istream& operator>>(std::istream& ist, Triangle& triangle){
    std::cout << "Введите координаты трех точек\n";
    double x, y;
    for (int i = 0; i < 3; ++i) {
        ist >> x >> y;
        triangle.points.push_back(Point(x, y));
    }

    // Проверка на то, что точки не лежат на одной прямой
    double a = Point::find_len(triangle.points[0].x_point, triangle.points[1].x_point, triangle.points[0].y_point, triangle.points[1].y_point);
    double b = Point::find_len(triangle.points[1].x_point, triangle.points[2].x_point, triangle.points[1].y_point, triangle.points[2].y_point);
    double c = Point::find_len(triangle.points[2].x_point, triangle.points[0].x_point, triangle.points[2].y_point, triangle.points[0].y_point);

    if (a + b <= c || a + c <= b || b + c <= a) {
        std::cerr << "Это не треугольник!";
        exit(-1);
    }

    return ist;
}