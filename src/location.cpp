// SPDX-FileCopyrightText: 2023 Jörg Strebel <email>
// SPDX-License-Identifier: Apache-2.0

#include "location.h"
#include "constants.h"
#include <random>


Location::Location(int px, int py, bool transp, int veg) 
    {
        std::random_device r;
        std::default_random_engine e1(r());
        std::uniform_int_distribution<int> uniform_dist(1, Constants::MAXYIELD);
        maxyield  = uniform_dist(e1);         
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
