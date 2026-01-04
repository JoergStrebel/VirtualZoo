#ifndef LINE_H
#define LINE_H

#include "worldmodel/Point.h"
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef Kernel::Vector_2 CGAL_Vector_2;

/**
 * Line segment defined by its starting and ending points
 */
class Line
{
public:
    const Point p1;
    const Point p2;
    Line(const Point& p1, const Point& p2);
    CGAL_Vector_2 toVector() const;

private:
        
};

#endif // LINE_H
