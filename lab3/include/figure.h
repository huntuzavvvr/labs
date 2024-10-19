#ifndef FIGURE_H
#define FIGURE_H
#include <vector>
#include "point.h"

class Figure{
    protected:
        std::vector<Point> points;
    public:
        Figure();
        Figure(std::vector<Point> points);
        Figure(const Figure& other);
        Figure(Figure&& figure);
        Figure& operator=(const Figure& other);
        Figure& operator=(Figure&& other) noexcept;
        bool operator==(const Figure& other) const;
        std::vector<Point> get_points() const;
        virtual operator double() = 0;
        virtual Point find_center() = 0;
        virtual ~Figure() = default;
        friend std::ostream& operator<<(std::ostream& ost, const Figure& figure);
        // virtual std::istream& operator>>(std::istream& ost, Figure& figure) = 0;
};

#endif