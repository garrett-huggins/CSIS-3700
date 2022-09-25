#include "point.h"

bool Intersect(Point p1, Point p2, Point q1, Point q2, Point &x);
bool InsidePolygon(Point p, Point c, int32_t qSize, Point q[], Point &x);

int main() {

    Point 
        o(0,0), // origin
        b, // opposite corner
        x; // point of intersection

    int32_t 
        n, // n <= 100 lines
        k, // 3 <= k <= 20 vertices
        m; // m <= 10 number of darts thrown

    // // test1
    // // (10/1,10/1)
    // // 2
    // // 3 (0/1,0/1) (3/1,0/1) (2/1,1/1)
    // // 4 (5/1,1/1) (8/1,4/1) (5/1,7/1) (2/1,4/1)
    // // 1
    // // (4/1,9/2)


    std::cin >> b;
    std::cin >> n;

    Point* polygon[n]; // n <= 100 polygons that point to 3 <= k <= 20  vertices

    int32_t polygonSize[n]; // how many vertices are in each polygon

    for (int32_t i=0; i < n; i++) {
        std::cin >> k;
        Point* vertices = new Point[k]; // array of vertices for each polygon
        polygonSize[i] = k;

        Fraction sum(0,1); // sum of k vertices

        Point pointK; // pointK of input

        for (int32_t j=0; j < k; j++) {
            std::cin >> vertices[j];
            std::cout << vertices[j] << std::endl;
        }

        polygon[i] = vertices; // fill polygon with vertices

    }

    std::cin >> m; // number of darts thrown

    Point dart[m]; // array of darts thrown

    for (int32_t i=0; i < m; i++) {
        std::cin >> dart[i];
        std::cout << i << "dart: " << dart[i] << std::endl;
    }

    Point p1(1,1), p2(2,2), q1(1,2), q2(2,1);

    // DART TIME

    for (int32_t i=0; i < m; i++) {
        for (int32_t j=0; j < n; j++) {
            std::cout << "poly size: " << polygonSize[j] << std::endl;
            std::cout << InsidePolygon(dart[i], b, polygonSize[j], polygon[j], x) << std::endl;
        }  
    }

    return 0;
}

bool Intersect(Point p1, Point p2, Point q1, Point q2, Point &x) {
    Point r = p2 - p1; // distance from p1 to q2
    Point s = q2 - q1; // stance from q1 to q2

    Point v = q1 - p1; // distance from q1 to p1
    Fraction d = r * s; // cross product of r and s

    // check r and s aren't parellel
    if (d != 0) {
        Fraction t = (v * s) / d; // intersection point along P in units of r
        Fraction u = (v * r) / d; // intersection point along Q in units of s

        if (t > 0 && t < 1 && u > 0 && u < 1) {
            x = p1 + (r * t);
            return true;
        }
    }
    return false;
}

bool InsidePolygon(Point p, Point c, int32_t qSize, Point q[], Point &x) {
    int32_t w = 0; // winding number

    Point 
    // verticle boundaries
        v1(p.getX(), 0),
        v2(p.getX(), c.getY()),

    // horizontal boundaries
        h1(0, p.getY()),
        h2(c.getX(), p.getY());

    Point 
        z1,
        z2;

    for (int32_t i=0; i<qSize; i++) {
        Point 
            qk = q[i], // vertex i
            qk1; // vertex i + 1

        // wrap vertices
        if (i+1 >= qSize) {
            qk1 = q[0];
        } else {
            qk1 = q[i+1];
        }
        std::cout << qk << " " << qk1 << std::endl;

        if (Intersect(v1, v2, qk, qk1, x)) {
            z1 = x - p;
            z2 = qk1 - qk;

            if (z1.getY() * z2.getX() < 0) {
                w = w + 1;
            } else {
                w = w - 1;
            }
        }

        if (Intersect(h1, h2, qk, qk1, x)) {
            z1 = x - p;
            z2 = qk1 - qk;

            if (z1.getX() * z2.getY() > 0) {
                w = w + 1;
            } else {
                w = w - 1;
            }
        }
    }
    if (w == 0) {
        return false;
    } else {
        return true;
    }
}