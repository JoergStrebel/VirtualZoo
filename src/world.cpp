// SPDX-FileCopyrightText: 2023 Jörg Strebel <email>
// SPDX-License-Identifier: Apache-2.0

#include "world.h"
#include "constants.h"
#include "sensor.h"
#include <cmath>
#include "Projection.h"

World::World()
= default;

void World::run_world(){
    this->check_collisions();
    this->create_visual_impression();
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
            //send stimulus to the organism
            myOrg.physical_stimulus(currentsens->get_id());
        }
        //check collision between the organism and locations
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

void World::create_visual_impression(){
    //TODO: create a vector containing projections from the objects / shapes in the world
    auto allLocs = allobjects.getLocations();
    // 1. loop over all lines in all location objects
    // 2. calculate the relative radians of each of the two points in the line
    // 3. sort all points by their relative radians
    // 4. check whether the point is visible, i.e. is not occluded by another line
    // 5. check the need to split a line: if the two points of a line have different visibilities, split the line and introduce another point
    // 6. calculate the depth of each visible point

    //hand over the projections to the organism as a visual stimulus

}
