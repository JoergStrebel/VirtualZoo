// SPDX-FileCopyrightText: 2023 Jörg Strebel <email>
// SPDX-License-Identifier: Apache-2.0

#include "world.h"
#include "constants.h"
#include "stimulus.h"

World::World()
{

}

void World::run_world(){
    this->check_collisions();
    myOrg.act();
}

void World::check_collisions(){

    //check collision between organism and boundary
    /*
    myOrg.y=std::min(myOrg.y, Constants::MAXY-Constants::ENTITYSIZE);
    myOrg.x=std::min(myOrg.x, Constants::MAXX-Constants::ENTITYSIZE);
    myOrg.y=std::max(myOrg.y, 0);
    myOrg.x=std::max(myOrg.x, 0);
    */
    if (myOrg.x<=0 ||
        myOrg.y<=0 ||
        myOrg.y >= Constants::MAXY-Constants::ENTITYSIZE ||
        myOrg.x >= Constants::MAXX-Constants::ENTITYSIZE) {
        //send stimulus to organism
        stimulus* colldectect = new stimulus("collision",nullptr);
        myOrg.physical_stimulus(colldectect);
    }
}

