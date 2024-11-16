#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>
#include <type_traits>
#include <cmath>

template<typename T>
concept Scalar = std::is_scalar_v<T>;

template<Scalar T>
class Point{ 
    public:
        T x_point;
        T y_point;
        Point(): x_point(0), y_point(0) {}
        Point(T x, T y): x_point(x), y_point(y) {}
        Point(const Point& other){
            x_point = other.x_point;
            y_point = other.y_point;
        }
        Point(Point&& other) noexcept {
            x_point = other.get_x();
            y_point = other.get_y();
            other.x_point = 0.0;
            other.y_point = 0.0;
        }
        T distance_to(const Point<T>& other) const {
            T dx = x_point - other.x_point;
            T dy = y_point - other.y_point;
            return std::sqrt(dx * dx + dy * dy);
        }
        Point& operator=(const Point& other){
            x_point = other.x_point;
            y_point = other.y_point;
            return *this;
        }
        Point& operator=(Point&& other){
            x_point = other.x_point;
            y_point = other.y_point;
            other.x_point = 0.0;
            other.y_point = 0.0;
            return *this;
        }
        T get_x() const {
            return this->x_point;
        }
        T get_y() const {
            return this->y_point;
        }
        bool operator==(const Point& other) const {
            return x_point == other.x_point && y_point == other.y_point;
        }
        bool operator!=(const Point& other) const {
            return !(*this == other);
        }
        
        static double find_len(double x1, double x2, double y1, double y2) {
            return std::sqrt(std::pow(x1 - x2, 2) + std::pow(y1 - y2, 2));
        }
};
#endif