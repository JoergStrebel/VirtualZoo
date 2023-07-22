// SPDX-FileCopyrightText: 2023 Jörg Strebel <email>
// SPDX-License-Identifier: Apache-2.0

#ifndef WORLD_H
#define WORLD_H

#include <string>
#include "locations.h"
#include "organism.h"

/**
 * This class represents the simulated world.
 */
class World
{
public:     
     /**
     * Default constructor
     */
    World();
    void run_world();

    Locations allobjects;
    Organism* myOrg;
    
private:


};

#endif // WORLD_H
