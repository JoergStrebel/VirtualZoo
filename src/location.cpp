// SPDX-FileCopyrightText: 2023 Jörg Strebel <email>
// SPDX-License-Identifier: Apache-2.0

#include "location.h"
#include "constants.h"
#include "sim_util.h"
#include "colour.h"

Location::Location(int px, int py, bool transp, int veg, std::string name, Colour col) : name(name), top_left(px, py), 
bottom_right(px+Constants::ENTITYSIZE, py+Constants::ENTITYSIZE), color(col)
    {
        maxyield  = rndnum.randomint(1, Constants::MAXYIELD);
        availableyield = maxyield;        
        vegetation = veg;
        transparency = transp;                
    }


const std::string Location::toString()
{
    return "Maxyield: "+std::to_string(maxyield);
}

const std::string Location::getName()
{
    return name;
}

const Point Location::getTopLeft()
{
    return top_left;
}
const Point Location::getBottomRight()
{
    return bottom_right;
}

