#ifndef SQUARE_H
#define SQUARE_H
#include "figure.h"

class Square: public Figure{
    public:
        operator double() override;
        Point find_center() override;
        friend std::istream& operator>>(std::istream& ist, Square& square);
        double dot_product(const Point& p1, const Point& p2, const Point& p3);
};  

#endif