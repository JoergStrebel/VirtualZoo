#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Point.h"
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Iso_rectangle_2.h>
#include <array>

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Iso_rectangle_2<Kernel> CGALRectangle;
typedef Kernel::Point_2 CGAL_Point_2;

// Forward declaration for Line
class Line;

/**
 * Rectangle defined as an axis-aligned bounding box using CGAL
 */
class Rectangle
{
public:
    /**
     * Constructs a rectangle from four lines representing its sides.
     * The lines are vectors and need to have a consistent orientation, hence they should be provided in the order: top, right, bottom, left.
     */
    Rectangle(const Line& l1, const Line& l2, const Line& l3, const Line& l4);

    /**
     * Returns the underlying CGAL iso-oriented rectangle
     */
    [[nodiscard]] const CGALRectangle& getGeometry() const;

    /**
     * Returns the four sides as Line objects (top, right, bottom, left)
     */
    [[nodiscard]] std::array<Line, 4> getSides() const;

private:
    CGALRectangle rectangle;

    /**
     * Converts four Line objects to a CGAL Iso_rectangle_2
     */
    static CGALRectangle linesToRectangle(const Line& l1, const Line& l2, const Line& l3, const Line& l4);
};

#endif // RECTANGLE_H
