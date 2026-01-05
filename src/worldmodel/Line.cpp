#include "Line.h"

Line::Line(const Point& p1, const Point& p2) : segment(
    CGAL_Point_2(p1.getX(), p1.getY()),
    CGAL_Point_2 (p2.getX(), p2.getY()))
{
}

Point Line::getStartPoint() const {
    return {segment.point(0)};
}

Point Line::getEndPoint() const {
    return {segment.point(1)};
}
