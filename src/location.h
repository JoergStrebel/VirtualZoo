// SPDX-FileCopyrightText: 2023 Jörg Strebel <email>
// SPDX-License-Identifier: Apache-2.0

#ifndef LOCATION_H
#define LOCATION_H

#include <string>
#include "sim_util.h"
#include "Point.h"
#include "Line.h"
#include "Rectangle.h"
#include "constants.h"
#include "colour.h"

/**
 * A location defines a place for an object or a patch of land with certain properties (extent ...). 
 */
class Location
{
private:        
    Point top_left;
    Point bottom_right;
    int vegetation;
    bool transparency;
    int maxyield;
    const std::string name;
    sim_util rndnum;
    const Rectangle area;
    const Colour color; 
    
public:
    int availableyield;
    Location(int px, int py, bool transp, int veg, std::string_view name, Colour col);
    const std::string toString();    
    const std::string getName();
    const Point getTopLeft();
    const Point getBottomRight();
    const Rectangle& getArea();    
};

#endif
