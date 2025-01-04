// SPDX-FileCopyrightText: 2023 Jörg Strebel <email>
// SPDX-License-Identifier: Apache-2.0

#include "world.h"
#include "constants.h"
#include "sensor.h"
#include <cmath>

World::World()
{

}

void World::run_world(){
    this->check_collisions();
    myOrg.act();
}

void World::check_collisions(){

    auto allLocs = allobjects.getLocations();    
    for(int i=0;i<=7;i++){
        sensor* currentsens = myOrg.sensorarray[i];
        
        //Calculate effective world coordinates of sensor
        int x = std::round(myOrgMan.x)+Constants::ENTITYSIZE/2+currentsens->x;
        int y = std::round(myOrgMan.y)+Constants::ENTITYSIZE/2+currentsens->y;
        
        //check collision between organism and world boundaries
        if (x<=0 ||
            y<=0 ||
            y >= Constants::MAXY ||
            x >= Constants::MAXX) {
            //send stimulus to organism            
            myOrg.physical_stimulus(currentsens->get_id());
        }
        //check collision between organism and locations
        for (Location* loc :allLocs){
            if (x>=loc->getTopLeft().x &&
                x<=loc->getBottomRight().x &&
                y >= loc->getTopLeft().y &&
                y <= loc->getBottomRight().y) {
            //send stimulus to organism            
                myOrg.physical_stimulus(currentsens->get_id());            
            }
        }
    }
}

