    #include "../include/rectangle.h"
    #include <iostream>
    #include <cmath>
    #include <vector>

    Rectangle::operator double(){
        double a = Point::find_len(points[0].x_point, points[1].x_point, points[0].y_point, points[1].y_point);
        double b = Point::find_len(points[1].x_point, points[2].x_point, points[1].y_point, points[2].y_point);
        return a * b;
    }

    Point Rectangle::find_center(){
        double x_center = (this->points[0].x_point + this->points[2].x_point) / 2;
        double y_center = (this->points[0].y_point + this->points[2].y_point) / 2;
        return Point(x_center, y_center);
    }

    double Rectangle::dot_product (const Point& p1, const Point& p2, const Point& p3){
        Point v1 = {p2.x_point - p1.x_point, p2.y_point - p1.y_point};
        Point v2 = {p3.x_point - p2.x_point, p3.y_point - p2.y_point};
        return v1.x_point * v2.x_point + v1.y_point * v2.y_point;
    }

    std::istream& operator>>(std::istream& ist, Rectangle& rectangle){
        std::cout << "Введите координаты левого верхнего и правого нижнего угла\n";
        double x, y;
        ist >> x >> y;
        Point p1(x, y);
        ist >> x >> y;
        Point p3(x, y);
        Point p2(p3.x_point, p1.y_point);
        Point p4(p1.x_point, p3.y_point);
        if (!(p1.x_point < p3.x_point && p1.y_point > p3.y_point)){
            std::cerr << "Неправильный ввод\n";
            exit(-1);
        }

        rectangle.points.push_back(p1);
        rectangle.points.push_back(p2);
        rectangle.points.push_back(p3);
        rectangle.points.push_back(p4);

        return ist;
    }