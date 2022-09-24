#include "point.h"

int main() {

    Point a(1,2), b (2,3);

    Fraction z = a * b;

    std::cout << z;

    return 0;
}