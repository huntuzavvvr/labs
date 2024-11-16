#include <gtest/gtest.h>
#include "rectangle.hpp"
#include "square.hpp"
#include "triangle.hpp"

TEST(RectangleTest, AreaCalculation) {
    Point<double> p1(0.0, 2.0);
    Point<double> p3(4.0, 0.0);
    Rectangle<double> rect = {p1, Point<double>(4.0, 2.0), p3, Point<double>(0.0, 0.0)};
    EXPECT_EQ(static_cast<double>(rect), 8.0);
}

TEST(RectangleTest, CenterCalculation) {
    Point<double> p1(0.0, 2.0);
    Point<double> p3(4.0, 0.0);
    Rectangle<double> rect = {p1, Point<double>(4.0, 2.0), p3, Point<double>(0.0, 0.0)};
    Point<double> center = rect.find_center();
    EXPECT_EQ(center.get_x(), 2.0);
    EXPECT_EQ(center.get_y(), 1.0);
}

TEST(RectangleTest, InputOperator) {
    std::stringstream ss;
    ss << "0.0 2.0 4.0 0.0";
    Rectangle<double> rect;
    ss >> rect;
    EXPECT_EQ(rect.get_points().size(), 4);
    EXPECT_EQ(rect.get_points()[0].get().get_x(), 0.0);
    EXPECT_EQ(rect.get_points()[0].get().get_y(), 2.0);
    EXPECT_EQ(rect.get_points()[2].get().get_x(), 4.0);
    EXPECT_EQ(rect.get_points()[2].get().get_y(), 0.0);
}

TEST(RectangleTest, DotProduct) {
    Point<double> p1(0.0, 0.0);
    Point<double> p2(1.0, 1.0);
    Point<double> p3(2.0, 2.0);
    Rectangle<double> rect;
    double dot_product = rect.dot_product(p1, p2, p3);
    EXPECT_EQ(dot_product, 2.0);
}


TEST(SquareTest, AreaCalculation) {
    Square<double> square{{Point<double>(0.0, 0.0), Point<double>(0.0, 2.0), Point<double>(2.0, 2.0), Point<double>(2.0, 0.0)}};
    EXPECT_DOUBLE_EQ(static_cast<double>(square), 4.0);
}

TEST(SquareTest, InputOperator) {
    std::stringstream ss;
    ss << "0.0 0.0 0.0 2.0 2.0 2.0 2.0 0.0";
    Square<double> square;
    ss >> square;
    EXPECT_EQ(square.get_points().size(), 4);
    EXPECT_DOUBLE_EQ(square.get_points()[0].get().get_x(), 0.0);
    EXPECT_DOUBLE_EQ(square.get_points()[0].get().get_y(), 0.0);
}

TEST(TriangleTest, AreaCalculation) {
    Triangle<double> triangle{{Point<double>(0.0, 0.0), Point<double>(4.0, 0.0), Point<double>(0.0, 3.0)}};
    EXPECT_DOUBLE_EQ(static_cast<double>(triangle), 6.0);
}

TEST(TriangleTest, InputOperator) {
    std::stringstream ss;
    ss << "0.0 0.0 4.0 0.0 0.0 3.0";
    Triangle<double> triangle;
    ss >> triangle;
    EXPECT_EQ(triangle.get_points().size(), 3);
    EXPECT_DOUBLE_EQ(triangle.get_points()[0].get().get_x(), 0.0);
    EXPECT_DOUBLE_EQ(triangle.get_points()[0].get().get_y(), 0.0);
}