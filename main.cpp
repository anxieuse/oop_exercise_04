/* 
Короткевич Л. В.
М8О-208Б-19
github.com/anxieuse/oop_exercise_04
Вариант 12:
    Ромб
    Трапеция
    Пятиугольник 
*/

#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>
#include <type_traits>
#include <tuple>

#include "Rhombus.hpp"
#include "Trapezoid.hpp"
#include "Pentagon.hpp"

// Figure Reading

template <typename T>
void readFigure(T &figure)
{
    int n = sizeof(figure.points) / sizeof(figure.points[0]);
    for (int i = 0; i < n; ++i) {
        std::cin >> figure.points[i].first >> figure.points[i].second;
    }
}

// Tuple Writing

template <typename T, size_t index>
typename std::enable_if<index == std::tuple_size<T>::value, void>::type printTuple(T &)
{
}

template <typename T, size_t index>
typename std::enable_if <index < std::tuple_size<T>::value, void>::type printTuple(T &tp)
{
    auto figure = std::get<index>(tp);
    std::cout << "Vertices of " << figure.name << ":\t";
    printVertices(figure);
    printTuple<T, index + 1>(tp);
}

template <typename T>
typename std::enable_if<(sizeof(T::points) / sizeof(T::points[0]) > 0), void>::type printVertices(T &figure)
{
    for (auto v : figure.points)
        std::cout << " ( " << v.first << ", " << v.second << " ) ";
    std::cout << std::endl;
}

// Area Calculations

template <class T, size_t index>
double totalTupleArea(T &tuple)
{
    auto figure = std::get<index>(tuple);
    double value = figureArea(figure);
    if constexpr ((index + 1) < std::tuple_size<T>::value)
    {
        return value + totalTupleArea<T, index + 1>(tuple);
    }
    return value;
} 

template <class T>
auto figureArea(T &figure)
{
    double area = 0;
    int n = sizeof(T::points) / sizeof(T::points[0]);
    for (int i = 1; i < n; ++i)
        area += figure.points[i - 1].first * figure.points[i].second - figure.points[i].first * figure.points[i - 1].second;
    area += figure.points[n - 1].first * figure.points[0].second - figure.points[0].first * figure.points[n - 1].second;
    return std::fabs(area) / 2.0;
}

void printHelp() 
{
    std::cout << "1) Add Rhombus\n";
    std::cout << "2) Add Trapeze\n";
    std::cout << "3) Add Pentagon\n";
    std::cout << "4) Display all the vertices of tuple's figures\n";
    std::cout << "5) Display total area of tuple's figures\n";
    std::cout << "6) Exit\n";
}

int main()
{
    printHelp();

    std::tuple<Rhombus<double>, Trapezoid<double>, Pentagon<int>> tp;

    int cmd;
    bool input = true;
    while (input) 
    {
        std::cin >> cmd;
        switch (cmd)
        {
        case 1: // add rhombus
        {
            readFigure(std::get<0>(tp));
            std::cout << std::get<0>(tp).name << " successfully added" << '\n';
            break;
        }
        case 2: // add trapezoid
        {
            readFigure(std::get<1>(tp));
            std::cout << std::get<1>(tp).name << " successfully added" << '\n';
            break;
        }
        case 3: // add pentagon
        {
            readFigure(std::get<2>(tp));
            std::cout << std::get<2>(tp).name << " successfully added" << '\n';
            break;
        }
        case 4: // print all
        {
            printTuple<decltype(tp), 0>(tp);
            break;
        }
        case 5: // total area
        {
            std::cout << "Total area of tuple's figures: " << totalTupleArea<decltype(tp), 0>(tp) << '\n';
            break;
        }
        case 6:
        {
            input = false;
            std::cout << "Exit" << '\n';
            break;
        }
        }
    }
    return 0;
}