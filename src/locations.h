// SPDX-FileCopyrightText: 2023 Jörg Strebel <email>
// SPDX-License-Identifier: Apache-2.0

#ifndef LOCATIONS_H
#define LOCATIONS_H

#include <vector>
#include "location.h"


/**
 * A summary class that stores all objects of the simulated environment
 */
class Locations
{
private:
    std::vector<Location> allobjects;
    
public:
    /**
     * Default constructor
     */
    Locations();

    
    /**
     * @todo write docs
     *
     * @param other TODO
     * @return TODO
     */
    bool operator==(const Locations& other) const;

    
};

#endif // LOCATIONS_H
