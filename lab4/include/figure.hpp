#ifndef FIGURE_HPP
#define FIGURE_HPP
#include <vector>
#include "point.hpp"
#include <memory>

template<Scalar T>
class Figure{
    protected:
        std::vector<std::unique_ptr<Point<T>>> points;
    public:
        Figure(){ 
            this->points = std::vector<std::unique_ptr<Point<T>>>();
        }
        Figure(const std::initializer_list<Point<T>> &vect){
            this->points.reserve(vect.size());
            for (const auto &elem : vect){
                this->points.push_back(std::make_unique<Point<T>>(elem));
            }
        }
        Figure(const Figure<T>& other){
            for (auto elem : other.get_points()){
                this->points.push_back(std::make_unique<Point<T>>(*elem)); //
            }
        }
        Figure(Figure&& other){
            this->points = std::move(other.get_points());
        }
        Figure<T>& operator=(const Figure<T>& other) {
            this->points.clear();
            for (auto elem : other.get_points()){
                this->points.push_back(std::make_unique<Point<T>>(*elem));
            }
            return *this;
        }
        Figure<T>& operator=(Figure<T>&& other) noexcept {
            this->points == std::move(other.get_points());
            return *this;
        }
        bool operator==(const Figure<T>& other) const {
            if (this->points.size() != other.get_points().size()){
                return false;
            }
            for (size_t i = 0; i < this->points.size(); ++i){
                if (*this->points[i] != *other.points[i]){
                    return false;
                }
            }
            return true;
        }
        std::vector<std::reference_wrapper<Point<T>>> get_points() const {
        std::vector<std::reference_wrapper<Point<T>>> result;
        for (const auto& ptr : this->points) {
            result.emplace_back(*ptr);
        }
        return result;
    }
        virtual operator double() = 0;
        virtual Point<T> find_center() = 0;
        virtual ~Figure() = default;
        friend std::ostream& operator<<(std::ostream& ost, const Figure<T>& figure) {
            for (auto elem : figure.get_points()){
                ost << elem;
                ost << '\n';
            }
            return ost;
        }
};

#endif