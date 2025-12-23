//
// Created by jstrebel on 10.05.25.
//

#ifndef PROJECTION_H
#define PROJECTION_H
#include "colour.h"

/**
 * A projection is a data transfer object that stores the data available to a retina (coming from a transformation of real-world shapes)
 * It stores pixels that are visible to the organism
 */
class Projection
{
public:
    Projection(double startrad, double startdepth, double endrad, double enddepth, const Colour& color );
    const double startrad;
    const double startdepth;
    const double endrad;
    const double enddepth;
    const Colour color;
};

#endif //PROJECTION_H
