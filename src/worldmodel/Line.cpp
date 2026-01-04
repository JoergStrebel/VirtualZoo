#include "Line.h"

Line::Line(const Point& p1, const Point& p2) : p1(p1), p2(p2)
{
}

CGAL_Vector_2 Line::toVector() const
{
    return CGAL_Vector_2(p2.getX() - p1.getX(), p2.getY() - p1.getY());
}
