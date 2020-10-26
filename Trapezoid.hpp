#pragma once

template<typename T>
class Trapezoid {
public:
    std::pair<T, T> points[4];
    std::string name = "Trapezoid";
};