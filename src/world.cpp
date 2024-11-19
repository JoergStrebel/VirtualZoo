// SPDX-FileCopyrightText: 2023 Jörg Strebel <email>
// SPDX-License-Identifier: Apache-2.0

#include "world.h"
#include "constants.h"
#include "sensor.h"

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
    
    for(int i=0;i<=7;i++){
        sensor* currentsens = myOrg.sensorarray[i];
        
        //Calculate effective world coordinates of sensor
        int x = myOrg.x+Constants::ENTITYSIZE/2+currentsens->x;
        int y = myOrg.y+Constants::ENTITYSIZE/2+currentsens->y;
    
        if (x<=0 ||
            y<=0 ||
            y >= Constants::MAXY ||
            x >= Constants::MAXX) {
            //send stimulus to organism            
            myOrg.physical_stimulus(currentsens->get_id());
        }   
    }
}

