// SPDX-FileCopyrightText: 2023 Jörg Strebel <email>
// SPDX-License-Identifier: Apache-2.0

#ifndef LOCATION_H
#define LOCATION_H

#include <string>
#include "sim_util.h"
#include "Point.h"

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
    
public:
    int availableyield;
    Location(int px, int py, bool transp, int veg, std::string name);
    std::string toString();
    sim_util rndnum;
    std::string getName();
    Point getTopLeft(); 

};

#endif
