#ifndef LINE_H
#define LINE_H

#include "worldmodel/Point.h"
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef Kernel::Segment_2 CGAL_Segment_2;
typedef Kernel::Point_2 CGAL_Point_2;

/**
 * Line segment defined by its starting and ending points
 */
class Line
{
public:
    Line(const Point& p1, const Point& p2);
    Point getStartPoint() const;
    Point getEndPoint() const;

private:
    const CGAL_Segment_2 segment;
};

#endif // LINE_H
