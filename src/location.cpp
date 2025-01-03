// SPDX-FileCopyrightText: 2023 Jörg Strebel <email>
// SPDX-License-Identifier: Apache-2.0

#include "location.h"
#include "constants.h"
#include "sim_util.h"


Location::Location(int px, int py, bool transp, int veg, std::string name) : name(name), top_left(px, py), 
bottom_right(px+Constants::ENTITYSIZE, py+Constants::ENTITYSIZE)
    {
        maxyield  = rndnum.randomint(1, Constants::MAXYIELD);
        availableyield = maxyield;        
        vegetation = veg;
        transparency = transp;                
    }


std::string Location::toString()
{
    return "Maxyield: "+std::to_string(maxyield);
}

std::string Location::getName()
{
    return name;
}

Point Location::getTopLeft()
{
    return top_left;
}
