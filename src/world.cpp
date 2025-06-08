// SPDX-FileCopyrightText: 2023 Jörg Strebel <email>
// SPDX-License-Identifier: Apache-2.0

#include "world.h"
#include "constants.h"
#include "sensor.h"
#include <cmath>
#include <list>

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
        int x = std::round(myOrgMan.x)+Constants::ENTITYSIZE/2.0+currentsens->x;
        int y = std::round(myOrgMan.y)+Constants::ENTITYSIZE/2.0+currentsens->y;
        
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
            //send stimulus to the organism
                myOrg.physical_stimulus(currentsens->get_id());            
            }
        }
    }
}

// Calculates the radians value of a point in the world relative to the organism's position
// 0.0 is heading west, pi/2 is heading north, pi is heading east, 3pi/2 is heading south
// counting is counterclockwise
float World::calculateRadians(float x, float y) const {
    float result=std::atan2(y - myOrgMan.y, x - myOrgMan.x);
    // Normalize the result to be in the range [0, 2*PI)
    if (result < 0) {
        result += 2 * Constants::PI; // Add 2*PI to make it positive
    }
    return result;

}

//create a private struct for the scanline algorithm
struct scanline_point{
    float pRad;
    Line line;
};

//Visibility check using a scanline algorithm
void World::create_visual_impression(){
    //TODO: create a vector containing projections from the objects / shapes in the world
    auto allLocs = allobjects.getLocations();
    std::vector<Projection> projections;
    std::list<scanline_point> sorted_points;

    for (Location* loc : allLocs)
    {
        Rectangle area = loc->getArea();
        // 1. loop over all lines in all location objects
        for (const Line& line : area.sides)
        {
            // 2. calculate the relative radians of each of the two points in the line
            auto p1Rad = scanline_point{
                this->calculateRadians(line.p1.x - myOrgMan.x, line.p1.y - myOrgMan.y), line};
            auto p2Rad =  scanline_point{
                this->calculateRadians(line.p2.x - myOrgMan.x, line.p2.y - myOrgMan.y), line};

            // add the points to the sorted list
            sorted_points.push_back(p2Rad);
            sorted_points.push_back(p1Rad);
        }
        // 3. sort all points by their relative radians
        sorted_points.sort([](const scanline_point& a, const scanline_point& b) {
            return a.pRad < b.pRad;
        });

        // 4. check whether the point is visible, i.e. is not occluded by another line
        // 5. create a projection for the visible points
        // 5. check the need to split a line: if the two points of a line have different visibilities, split the line and introduce another point
        // 6. calculate the depth of each visible point
        //float startDepth = std::hypot(line.p1.x - myOrgMan.x, line.p1.y - myOrgMan.y);
        //float endDepth = std::hypot(line.p2.x - myOrgMan.x, line.p2.y - myOrgMan.y);
    }
    //hand over the projections to the organism as a visual stimulus
}

