// SPDX-FileCopyrightText: 2023 Jörg Strebel <email>
// SPDX-License-Identifier: Apache-2.0

#include "locations.h"
#include "constants.h"

Locations::Locations()
{
    allobjects.push_back(new Location(100, 100, false, Constants::Vegetation_Constants::PLANT, "bush"));
    allobjects.push_back(new Location(300, 100, false, Constants::Vegetation_Constants::PLANT, "bush"));
}

std::vector<Location*> Locations::getLocations(){
    return allobjects;
}
