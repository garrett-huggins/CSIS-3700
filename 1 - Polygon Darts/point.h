#include <iostream>
#include "fraction.h"

#ifndef _POINT_H
#define _POINT_H


class Point {
    private:
        Fraction x, y;

    public:
        Point(Fraction _x=0, Fraction _y=0);
        ~Point(void);

        // assignment
        Point &operator=(Point rhs);

        // add and subtract
        Point operator+(Point rhs);
        Point operator-(Point rhs);

        // cross product of 2 points
        Fraction operator*(Point rhs);
        // multiply by Fraction
        Point operator*(Fraction rhs);

        // comparison operators
        bool operator==(Point rhs);
        bool operator!=(Point rhs);

        // getters
        Fraction getX() { return x; }
        Fraction getY() { return y; }
};

std::istream &operator>>(std::istream &is, Point &p);
std::ostream &operator<<(std::ostream &os, Point p);

#endif
