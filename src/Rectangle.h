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
    const std::array<Line, 4> sides;    
    Rectangle(const Line& l1, const Line& l2, const Line& l3, const Line& l4);

private:
        
};

#endif // RECTANGLE_H
