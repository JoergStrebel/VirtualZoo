// SPDX-FileCopyrightText: 2023 Jörg Strebel <email>
// SPDX-License-Identifier: Apache-2.0

#include "world.h"
#include "constants.h"
#include "sensor.h"
#include <cmath>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include "Projection.h"
#include <CGAL/intersections.h>

using K = CGAL::Exact_predicates_inexact_constructions_kernel;
using Point_2 = K::Point_2;
using Ray_2 = K::Ray_2;
using Segment_2 = K::Segment_2;


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
double World::calculateRadians(double x, double y) const {
    return normalize(std::atan2(y - myOrgMan.y, x - myOrgMan.x));
}

// Helper function to calculate the squared distance between two points
float World::distanceSquared(const float x1, const float y1, const float x2, const float y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    return dx * dx + dy * dy;
}

double World::normalize(double radvalue) {
    while (radvalue < 0) radvalue += 2.0 * Constants::PI;
    while (radvalue >= 2.0 * Constants::PI) radvalue -= ((double)2.0) * Constants::PI;
    return radvalue;
}

double World::heading_to_rad(double heading) {
    // 0.0 is heading north, 90.0 is heading east, 180.0 is heading south, 270.0 is heading west
    // counting is clockwise
    double angle = 360 +(90.0 - heading);
    return normalize((angle / 360.0) * 2.0 * Constants::PI);
}

/* Render the locations in the world as a visual impression for the organism
 * Uses an angular sweep algorithm to determine visible portions of lines in the world
 */
void World::create_visual_impression(){
    std::vector<Projection> projections;
    std::vector<AngleEvent> angleEvents;
    
    // Collect all angle events from locations
    collectAngleEvents(angleEvents);

    // Perform angular sweep
    float lastAngle = -1.0f;
    float lastDepth = -1.0f;
    int lastLocationIndex = -1;

    for (const auto& event : angleEvents) {
        double currentAngle = normalize(event.angle);

    }

    // Filter projections by field of view
    std::vector<Projection> filteredProjections = filterProjectionsByFOV(projections);

    // Hand over the projections to the organism as a visual stimulus
    myOrg.visual_stimulus(filteredProjections);
}

// Collects all angle events from locations and sorts them by angle
void World::collectAngleEvents(std::vector<AngleEvent>& angleEvents) {
    const auto allLocs = allobjects.getLocations();
    int locationIndex = 0;

    for (Location* loc : allLocs) {
        Rectangle area = loc->getArea();
        //TODO: get vertices of rectangle and create angle events for each vertex
        auto sides = area.getSides();

        for (const Line& line : sides) {
            double x1 = line.getStartPoint().getX();
            double y1 = line.getStartPoint().getY();
            double x2 = line.getEndPoint().getX();
            double y2 = line.getEndPoint().getY();
            
            // Calculate angles for both endpoints
            double angle1 = calculateRadians(x1, y1);
            double angle2 = calculateRadians(x2, y2);
            
            // Add events for both endpoints
            angleEvents.emplace_back(angle1, &line, locationIndex, true);
            angleEvents.emplace_back(angle2, &line, locationIndex, true);
        }
        locationIndex++;
    }
    
    // Sort events by angle
    std::sort(angleEvents.begin(), angleEvents.end(), 
              [](const AngleEvent& a, const AngleEvent& b) {
                  return a.angle < b.angle;
              });
}

// Filters projections by the organism's field of view
std::vector<Projection> World::filterProjectionsByFOV(const std::vector<Projection>& projections) {
    std::vector<Projection> filteredProjections;
    double halfFOVrad = myOrgMan.field_of_view_rad / 2.0;
    double orgHeadingRad = heading_to_rad(myOrgMan.heading);
    double leftBound = normalize(orgHeadingRad + halfFOVrad);
    double rightBound = normalize(orgHeadingRad - halfFOVrad);

}

