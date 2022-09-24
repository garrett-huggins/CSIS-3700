#include "fraction.h"

#ifndef _POINT_H
#define _POINT_H


class Point {
    private:
        Fraction x, y;

    public:
        Point(Fraction x=0, Fraction y=0);
        ~Point(void);

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


#endif
