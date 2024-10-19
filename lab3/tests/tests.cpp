#include <gtest/gtest.h>
#include <sstream>
#include "../include/rectangle.h"
#include "../include/square.h"
#include "../include/triangle.h"

// Тестирование класса Rectangle
TEST(RectangleTest, AreaAndCenter) {
    Rectangle rect;
    std::istringstream iss("0 10 10 0");
    iss >> rect;

    double area = static_cast<double>(rect);
    Point center = rect.find_center();

    EXPECT_NEAR(area, 100.0, 1e-9);
    EXPECT_NEAR(center.x_point, 5.0, 1e-9);
    EXPECT_NEAR(center.y_point, 5.0, 1e-9);
}

// Тестирование класса Square
TEST(SquareTest, AreaAndCenter) {
    Square square;
    std::istringstream iss("0 0 10");
    iss >> square;

    double area = static_cast<double>(square);
    Point center = square.find_center();

    EXPECT_NEAR(area, 100.0, 1e-9);
    EXPECT_NEAR(center.x_point, 5.0, 1e-9);
    EXPECT_NEAR(center.y_point, -5.0, 1e-9);
}

// // Тестирование класса Triangle
TEST(TriangleTest, AreaAndCenter) {
    Triangle triangle;
    std::istringstream iss("0 0 10 0 0 10");
    iss >> triangle;

    double area = static_cast<double>(triangle);
    Point center = triangle.find_center();

    EXPECT_NEAR(area, 50.0, 1e-9);
    EXPECT_NEAR(center.x_point, 10.0 / 3, 1e-9);
    EXPECT_NEAR(center.y_point, 10.0 / 3, 1e-9);
}

// // Тестирование некорректного ввода для Rectangle
TEST(RectangleTest, InvalidInput) {
    Rectangle rect;
    std::istringstream iss("0 0 0 0");
    EXPECT_DEATH(iss >> rect, "Неправильный ввод");
}

// // Тестирование некорректного ввода для Triangle
TEST(TriangleTest, InvalidInput) {
    Triangle triangle;
    std::istringstream iss("0 0 10 0 20 0");
    EXPECT_DEATH(iss >> triangle, "Это не треугольник!");
}