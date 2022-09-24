#include "point.h"
#include "fraction.h"

Point::Point(Fraction a, Fraction b) {
    x = a;
    y = b;
}

Point::~Point(void) {}

Point Point::operator+(Point rhs) {
    Fraction s,t;

    s = x + rhs.x;
    t = y + rhs.y;

    return Point(s,t);
}

Point Point::operator-(Point rhs) {
    Fraction s,t;

    s = x - rhs.x;
    t = y - rhs.y;

    return Point(s,t);
}

Fraction Point::operator*(Point rhs) {
    Fraction z;

    z = (x * rhs.y) - (y * rhs.x);

    return z;
}

Point Point::operator*(Fraction rhs) {
    Fraction s,t;

    s = x * rhs;
    t = y * rhs;

    return Point(s,t);
}

bool Point::operator==(Point rhs) {
    return x == rhs.x && y == rhs.y;
}

bool Point::operator!=(Point rhs) {
    return x != rhs.x && y != rhs.y;
}