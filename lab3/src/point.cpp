#include "../include/point.h"
#include <cmath>


Point::Point(): x_point(0), y_point(0) {}
Point::Point(double x, double y): x_point(x), y_point(y){}
Point::Point(const Point& other){
    x_point = other.x_point;
    y_point = other.y_point;
}
Point::Point(Point&& other) noexcept{
    x_point = other.get_x();
    y_point = other.get_y();
    other.x_point = 0.0;
    other.y_point = 0.0;
}
Point& Point::operator=(const Point& other){
    x_point = other.x_point;
    y_point = other.y_point;
    return *this;
}

Point& Point::operator=(Point&& other){
    x_point = other.x_point;
    y_point = other.y_point;
    other.x_point = 0.0;
    other.y_point = 0.0;
    return *this;
}

double Point::get_x() const{
    return this->x_point;
}

double Point::get_y() const{
    return this->y_point;
}

bool Point::operator==(const Point& other) const{
    return x_point == other.x_point && y_point == other.y_point;
}

bool Point::operator!=(const Point& other) const{
    return !(*this == other);
}

std::ostream &operator<<(std::ostream &ost, const Point &point)
{
    ost << "x = " << point.get_x() << ", y = " << point.get_y();
    return ost;
}

double Point::find_len(double x1, double x2, double y1, double y2) {
    return std::sqrt(std::pow(x1 - x2, 2) + std::pow(y1 - y2, 2));
}