#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "figure.hpp"

template<Scalar T>
class Triangle : public Figure<T> {
public:
    Triangle() : Figure<T>(){}
    Triangle(const std::initializer_list<Point<T>>& points) : Figure<T>(points) {
        if (this->points.size() != 3) {
            throw std::invalid_argument("Triangle must have exactly 3 points.");
        }
    }
    friend std::istream& operator>>(std::istream& is, Triangle<T>& triangle) {
        T x, y;
        std::vector<Point<T>> temp_points;
        for (size_t i = 0; i < 3; ++i) {
            if (!(is >> x >> y)) {
                throw std::runtime_error("Invalid input for Triangle.");
            }
            temp_points.emplace_back(x, y);
        }
        triangle.points.clear();
        for (const auto& point : temp_points) {
            triangle.points.push_back(std::make_unique<Point<T>>(point));
        }
        return is;
    }
    virtual operator double() override {
        T a = this->points[0]->distance_to(*this->points[1]);
        T b = this->points[1]->distance_to(*this->points[2]);
        T c = this->points[2]->distance_to(*this->points[0]);
        T s = (a + b + c) / 2;
        return std::sqrt(s * (s - a) * (s - b) * (s - c));
    }
    virtual Point<T> find_center() override {
        T x_sum = 0;
        T y_sum = 0;
        for (const auto& point : this->points) {
            x_sum += point->get_x();
            y_sum += point->get_y();
        }
        return Point<T>(x_sum / 3, y_sum / 3);
    }
};

#endif
