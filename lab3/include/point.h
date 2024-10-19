#ifndef POINT_H
#define POINT_H

#include <iostream>

class Point{ 
    public:
        double x_point;
        double y_point;
        Point();
        Point(double x, double y);
        Point(const Point& other);
        Point(Point&& other) noexcept;
        Point& operator=(const Point& other);
        Point& operator=(Point&& other);
        double get_x() const;
        double get_y() const;
        bool operator==(const Point& other) const;
        bool operator!=(const Point& other) const;
        
        static double find_len(double x1, double x2, double y1, double y2);
};
std::ostream& operator<<(std::ostream& ost, const Point& point);

#endif