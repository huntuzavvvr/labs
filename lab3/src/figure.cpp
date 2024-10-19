#include "../include/figure.h"
#include "../include/point.h"

Figure::Figure(){
    std::vector<Point> points;
    this->points = points;
}

Figure::Figure(std::vector<Point> points){
    this->points = points;
}

Figure::Figure(const Figure& other){
    std::vector<Point> new_points;

    for (auto elem : other.get_points()){
        new_points.push_back(elem);
    }
    this->points = new_points;
}

Figure::Figure(Figure&& other){
    this->points = std::move(other.get_points());
}

Figure& Figure::operator=(const Figure& other){
    std::vector<Point> new_points;

    for (auto elem : other.get_points()){
        new_points.push_back(elem);
    }
    this->points = new_points;
    return *this;
}

Figure& Figure::operator=(Figure&& other) noexcept{
    this->points == std::move(other.get_points());
    return *this;
}

bool Figure::operator==(const Figure& other) const{
    if (points.size() != other.get_points().size()){
        return false;
    }
    for (size_t i = 0; i < points.size(); ++i){
        if (points[i] != other.points[i]){
            return false;
        }
    }
    return true;
}

std::vector<Point> Figure::get_points() const{
    return this->points;
}

std::ostream& operator<<(std::ostream& ost, const Figure& figure){
    for (auto elem : figure.get_points()){
        ost << elem;
        ost << '\n';
    }
    return ost;
}