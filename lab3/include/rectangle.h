#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "figure.h"

class Rectangle: public Figure{
    public:
        // Rectangle(const std::vector<Point>& ost) : Figure(ost){}
        operator double() override;
        Point find_center() override;
        friend std::istream& operator>>(std::istream& ist, Rectangle& rectangle);
        double dot_product(const Point& p1, const Point& p2, const Point& p3);
};  

#endif