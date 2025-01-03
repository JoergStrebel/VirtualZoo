// SPDX-FileCopyrightText: 2023 Jörg Strebel <email>
// SPDX-License-Identifier: Apache-2.0

#ifndef WORLD_H
#define WORLD_H

#include <string>
#include "locations.h"
#include "organism.h"
#include "organism_manager.h"

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
    Organism_Manager myOrgMan;
    Organism myOrg{"beetle", myOrgMan};    
    
private:
    //checks collisions among objects and between objects and boundary
    //sends events to the affected objects, so that they can react on.
    void check_collisions();

};

#endif // WORLD_H
