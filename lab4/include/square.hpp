#ifndef SQUARE_HPP
#define SQUARE_HPP

#include "figure.hpp"

template<Scalar T>
class Square : public Figure<T> {
public:
    Square() : Figure<T>(){}
    Square(const std::initializer_list<Point<T>>& points) : Figure<T>(points) {
        if (this->points.size() != 4) {
            throw std::invalid_argument("Square must have exactly 4 points.");
        }
    }
    friend std::istream& operator>>(std::istream& is, Square<T>& square) {
        T x, y;
        std::vector<Point<T>> temp_points;
        for (size_t i = 0; i < 4; ++i) {
            if (!(is >> x >> y)) {
                throw std::runtime_error("Invalid input for Square.");
            }
            temp_points.emplace_back(x, y);
        }
        square.points.clear();
        for (const auto& point : temp_points) {
            square.points.push_back(std::make_unique<Point<T>>(point));
        }
        return is;
    }
    virtual operator double() override {
        T side = this->points[0]->distance_to(*this->points[1]);
        return side * side;
    }
    virtual Point<T> find_center() override {
        T x_sum = 0;
        T y_sum = 0;
        for (const auto& point : this->points) {
            x_sum += point->get_x();
            y_sum += point->get_y();
        }
        return Point<T>(x_sum / 4, y_sum / 4);
    }
};

#endif
