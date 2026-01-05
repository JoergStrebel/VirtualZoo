
#ifndef POINT_H
#define POINT_H

/**
 * Geometric Point in the world's 2d plane (i.e. a pixel)
 */
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef Kernel::Point_2 CGAL_Point;

class Point {
private:
    CGAL_Point point;

public:
    Point(double x, double y) : point(x, y) {}
    Point(const CGAL_Point& p) : point(p) {}

    double getX() const { return point.x(); }
    double getY() const { return point.y(); }

    void setX(double x) { point = CGAL_Point(x, point.y()); }
    void setY(double y) { point = CGAL_Point(point.x(), y); }
};

#endif // POINT_H
