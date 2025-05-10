//
// Created by jstrebel on 10.05.25.
//

#ifndef PROJECTION_H
#define PROJECTION_H

/**
 * A projection is a data transfer object that stores the data available to a retina (coming from a transformation of real-world shapes)
 * It stores pixels that are visible to the organism
 */
class Projection
{
public:
    Projection(float startrad, float startdepth, float endrad, float enddepth, int color );
    const float startrad;
    const float startdepth;
    const float endrad;
    const float enddepth;
    const int color;

};

#endif //PROJECTION_H
