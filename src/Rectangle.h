#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Line.h"
#include <array>

/**
 * Rectangle defined by its four sides
 */
class Rectangle
{
public:
//TODO: this should not be an array but a linked list, so that there is a well-defined starting point and order of the sides
    const std::array<Line, 4> sides;
    /**
     * Constructs a rectangle from four lines representing its sides.
     * The lines are vectors and need to have a consistent orientation, hence they should be provided in the order: top, right, bottom, left.
     */
    Rectangle(const Line& l1, const Line& l2, const Line& l3, const Line& l4);

private:
        
};

#endif // RECTANGLE_H
