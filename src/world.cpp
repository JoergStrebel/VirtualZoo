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
            if (x>=loc->getTopLeft().getX() &&
                x<=loc->getBottomRight().getX() &&
                y >= loc->getTopLeft().getY() &&
                y <= loc->getBottomRight().getY()) {
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

/* Render the locations in the world as a visual impression for the organism
 * TODO: create a vector containing projections from the objects / shapes in the world
 */
void World::create_visual_impression(){
    auto allLocs = allobjects.getLocations();
    std::vector<Projection> projections;
    std::list<scanline_point> sorted_points;
    //TODO: remove hidden surfaces by calculating the dot product of the orientation of the organism and the normal vector of the line

    //TODO: remove invisible surfaces by sorting out lines which are completely outside the view frustum
    //and by splitting lines where a part of the line is outside the view frustum


    //TODO: find visible parts of the lines
    for (Location* loc : allLocs)
    {
        Rectangle area = loc->getArea();
        // 1. loop over all lines in all location objects
        for (const Line& line : area.sides)
        {
            // 2. calculate the relative radians of each of the two points in the line
            auto p1Rad = scanline_point{
                this->calculateRadians(line.p1.getX() - myOrgMan.x, line.p1.getY() - myOrgMan.y), line};
            auto p2Rad =  scanline_point{
                this->calculateRadians(line.p2.getX() - myOrgMan.x, line.p2.getY() - myOrgMan.y), line};

            // add the points to the sorted list
            sorted_points.push_back(p2Rad);
            sorted_points.push_back(p1Rad);
        }
        // 3. sort all points by their relative radians
        sorted_points.sort([](const scanline_point& a, const scanline_point& b) {
            return a.pRad < b.pRad;
        });

        /* 4.Rank the points using a scanline algorithm
         * Start with the left-most point; if there are more than one, take the one with the smallest distance and mark the others as invisible
         * start iterating through the sorted points.
         * Check if there are lines in front of it or behind it. To do so,
         * - construct the line segment from the organism through the point and
         * - intersect it with the lines having smaller radians starting points and bigger radians ending points.
         *      if there are no intersections, mark point as visible XOR
         *      if there are intersection points in front of it, mark point as invisible. XOR
         *      if there are intersection points behind it and if the point is a start point, insert the intersection point on the line behind it as an end point and mark both the new point and the point as visible. XOR
         *      if there are intersection points behind it and if the point is an end point, insert the intersection point on the line behind it as a start point and mark both the new point and the point as visible.
         *
         * At the end of the scanline algorithm, we have a list of visible start / end points. Only lines segments with a visible start and end point are visible in total.
         */

    }
    //hand over the projections to the organism as a visual stimulus
}

