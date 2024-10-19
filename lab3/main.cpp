#include <iostream>
#include "include/rectangle.h"
#include "include/square.h"
#include "include/triangle.h"
#include "include/point.h"

int main() {
    int numFigures = 0;
    int index = 0;
    char type;
    double totalArea = 0.0;
    std::cout << "Введите количество фигур" << std::endl;
    std::cin >> numFigures;
    Figure** figures = new Figure*[numFigures];

    while (index < numFigures) {
        std::cout << "Введите r-прямоугольник, s-квадрат, t-треугольник" << std::endl;
        std::cin >> type;
        switch (type) {
            case 'r': {
                Rectangle* rect = new Rectangle();
                std::cin >> *rect;
                figures[index] = rect;
                break;
            }
            case 's': {
                Square* sq = new Square();
                std::cin >> *sq;
                figures[index] = sq;
                break;
            }
            case 't': {
                Triangle* tri = new Triangle();
                std::cin >> *tri;
                figures[index] = tri;
                break;
            }
            default:
                std::cout << "Неизвестный тип фигуры.\n";
                continue;
        }
        totalArea += double(*figures[index]);
        ++index;
    }

    char command;

    while (true) {
        std::cout << "Введите команду, которая вам нужна: a - общая площадь, r - удалить фигуру, c - центр фигуры, e - выйти \n";
        std::cin >> command;
        switch (command) {
            case 'a':
                std::cout << "Площадь: " << totalArea << std::endl;
                break;
            case 'r': {
                std::cout << "Введите индекс\n";
                int ind = 0;
                std::cin >> ind;
                if (ind >= 0 && ind < numFigures) {
                    totalArea -= double(*figures[ind]);
                    delete figures[ind];
                    for (int i = ind; i < numFigures - 1; ++i) {
                        figures[i] = figures[i + 1];
                    }
                    figures[numFigures - 1] = nullptr;
                    --numFigures;
                } else {
                    std::cout << "Неверный индекс\n";
                }
                break;
            }
            case 'c': {
                std::cout << "Введите индекс\n";
                int ind = 0;
                std::cin >> ind;
                if (ind >= 0 && ind < numFigures) {
                    Point center = figures[ind]->find_center();
                    std::cout << "Центр фигуры: (" << center.x_point << ", " << center.y_point << ")\n";
                } else {
                    std::cout << "Неверный индекс\n";
                }
                break;
            }
            case 'e':
                for (int i = 0; i < numFigures; ++i) {
                    delete figures[i];
                }
                delete[] figures;
                return 0;
            default:
                std::cout << "Неизвестная команда\n";
        }
    }
}