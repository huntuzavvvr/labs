#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "figure.hpp"


template<Scalar T>
class Rectangle: public Figure<T>{
    public:
        Rectangle() : Figure<T>(){}
        Rectangle(const std::initializer_list<Point<T>>& points) : Figure<T>(points){
            if (points.size() != 4) {
                throw std::invalid_argument("Rectangle must have exactly 4 points.");
            }
        }

        operator double() override {
        double a = Point<T>::find_len(this->points[0]->x_point, this->points[1]->x_point,
                                      this->points[0]->y_point, this->points[1]->y_point);
        double b = Point<T>::find_len(this->points[1]->x_point, this->points[2]->x_point,
                                      this->points[1]->y_point, this->points[2]->y_point);
        return a * b;
    }
        Point<T> find_center() override {
        double x_center = (this->points[0]->x_point + this->points[2]->x_point) / 2;
        double y_center = (this->points[0]->y_point + this->points[2]->y_point) / 2;
        return Point<T>(x_center, y_center);
    }
        friend std::istream& operator>>(std::istream& ist, Rectangle<T>& rectangle){
            std::cout << "Введите координаты левого верхнего и правого нижнего угла\n";
            T x, y;
            ist >> x >> y;
            Point<T> p1(x, y);
            ist >> x >> y;
            Point<T> p3(x, y);
            Point<T> p2(p3.x_point, p1.y_point);
            Point<T> p4(p1.x_point, p3.y_point);
            if (!(p1.x_point < p3.x_point && p1.y_point > p3.y_point)){
                std::cerr << "Неправильный ввод\n";
                exit(-1);
            }

            rectangle.points.push_back(std::make_unique<Point<T>>(p1));
            rectangle.points.push_back(std::make_unique<Point<T>>(p2));
            rectangle.points.push_back(std::make_unique<Point<T>>(p3));
            rectangle.points.push_back(std::make_unique<Point<T>>(p4));

            return ist;
        }
        double dot_product(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3){
            Point<T> v1 = {p2.x_point - p1.x_point, p2.y_point - p1.y_point};
            Point<T> v2 = {p3.x_point - p2.x_point, p3.y_point - p2.y_point};
            return v1.x_point * v2.x_point + v1.y_point * v2.y_point;
        }
};  

#endif