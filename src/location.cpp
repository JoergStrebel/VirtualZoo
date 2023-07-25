// SPDX-FileCopyrightText: 2023 Jörg Strebel <email>
// SPDX-License-Identifier: Apache-2.0

#include "location.h"
#include "constants.h"
#include "sim_util.h"


Location::Location(int px, int py, bool transp, int veg) 
    {

        sim_util rndnum;

        maxyield  = rndnum.randomint(1, Constants::MAXYIELD);
        availableyield = maxyield;
        
        xlo = px;
        ylo = py; 
        xru = px;
        yru = py; 
        vegetation = veg;
        transparency = transp;                
    }


std::string Location::toString()
{
    return "Maxyield: "+std::to_string(maxyield);
}
