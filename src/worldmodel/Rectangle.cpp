#include "Rectangle.h"
#include "worldmodel/Line.h"

Rectangle::Rectangle(const Line& l1, const Line& l2, const Line& l3, const Line& l4)
    : rectangle(linesToRectangle(l1, l2, l3, l4))
{
}

CGALRectangle Rectangle::linesToRectangle(const Line& l1, const Line& l2, const Line& l3, const Line& l4)
{
    // Extract the corner points from the lines
    // Lines are provided in order: top, right, bottom, left, clockwise orientation
    // Find min and max coordinates
    CGAL_Point_2 p1(l1.getStartPoint().getX(), l1.getStartPoint().getY());
    CGAL_Point_2 p2(l1.getEndPoint().getX(), l1.getEndPoint().getY());
    CGAL_Point_2 p3(l2.getEndPoint().getX(), l2.getEndPoint().getY());
    CGAL_Point_2 p4(l3.getEndPoint().getX(), l3.getEndPoint().getY());

    double minX = std::min({p1.x(), p2.x(), p3.x(), p4.x()});
    double maxX = std::max({p1.x(), p2.x(), p3.x(), p4.x()});
    double minY = std::min({p1.y(), p2.y(), p3.y(), p4.y()});
    double maxY = std::max({p1.y(), p2.y(), p3.y(), p4.y()});

    return {CGAL_Point_2(minX, minY), CGAL_Point_2(maxX, maxY)};
}

const CGALRectangle& Rectangle::getGeometry() const
{
    return rectangle;
}

std::array<Line, 4> Rectangle::getSides() const
{
    // Reconstruct the four sides from the rectangle
    // Order: top, right, bottom, left
    CGAL_Point_2 min_pt = rectangle.min();
    CGAL_Point_2 max_pt = rectangle.max();

    Point bottomLeft(min_pt.x(), min_pt.y());
    Point topRight(max_pt.x(), max_pt.y());
    Point topLeft(min_pt.x(), max_pt.y());
    Point bottomRight(max_pt.x(), min_pt.y());

    // Create lines in order: top, right, bottom, left
    Line top(topLeft, topRight);
    Line right(topRight, bottomRight);
    Line bottom(bottomRight, bottomLeft);
    Line left(bottomLeft, topLeft);

    return std::array<Line, 4>{top, right, bottom, left};
}