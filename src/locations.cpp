// SPDX-FileCopyrightText: 2023 Jörg Strebel <email>
// SPDX-License-Identifier: Apache-2.0

#include "locations.h"
#include "constants.h"

Locations::Locations()
{
    allobjects.push_back(Location(5, 5, false, Constants::Vegetation_Constants::PLANT));
    allobjects.push_back(Location(10, 5, false, Constants::Vegetation_Constants::PLANT));
}


bool Locations::operator==(const Locations& other) const
{
    return true;
}

