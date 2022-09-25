#include "point.h"
#include "fraction.h"

Point::Point(Fraction _x, Fraction _y) {
    x = _x;
    y = _y;
}

Point::~Point(void) {}

Point &Point::operator=(Point rhs) {
	x = rhs.x;
	y = rhs.y;

	return *this;
}

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

// istream and ostream mainly for testing purposes

std::istream &operator>>(std::istream &is, Point &p) {

	Fraction x,y;
	
	char comma, bracketLeft, bracketRight;

	is >> bracketLeft >> x >> comma >> y >> bracketRight;
	
	p = Point(x,y);
	
	return is;
}
std::ostream &operator<<(std::ostream &os, Point p) {

	os << "(" << p.getX() << " , " << p.getY() << ")";

	return os;
}
