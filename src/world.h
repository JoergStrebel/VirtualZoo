// SPDX-FileCopyrightText: 2023 Jörg Strebel <email>
// SPDX-License-Identifier: Apache-2.0

#ifndef WORLD_H
#define WORLD_H

#include "locations.h"


/**
 * This class represents the simulated world.
 */
class World
{
private:
     Locations allobjects;

public:     
     /**
     * Default constructor
     */
    World();
    
    /**
     * @todo write docs
     *
     * @param other TODO
     * @return TODO
     */
    bool operator==(const World& other) const;

};

#endif // WORLD_H
