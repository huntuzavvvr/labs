#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "figure.h"

class Triangle: public Figure{
    public:
        operator double() override;
        Point find_center() override;
        friend std::istream& operator>>(std::istream& ist, Triangle& triangle);
        double dot_product(const Point& p1, const Point& p2, const Point& p3);
};  

#endif