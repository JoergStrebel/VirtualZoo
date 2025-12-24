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
float World::calculateRadians(float x, float y) const {
    return normalize(std::atan2(y - myOrgMan.y, x - myOrgMan.x));
}

// Helper function to calculate the squared distance between two points
float World::distanceSquared(const float x1, const float y1, const float x2, const float y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    return dx * dx + dy * dy;
}

// Helper function to find ray-segment intersection
// Returns true if intersection exists, and sets intersection point and distance
// float& outX, float& outY, float& outDist are output parameters for intersection coordinates and distance
bool World::raySegmentIntersection(float rayAngle, const Line& segment, 
                                   float& outX, float& outY, float& outDist) const {
    const Point_2 rayOrigin(myOrgMan.x, myOrgMan.y);
    const Point_2 rayDirection(std::cos(rayAngle), std::sin(rayAngle));
    const Ray_2 ray(rayOrigin, rayDirection);

    Segment_2 seg(Point_2(segment.p1.getX(), segment.p1.getY()),
                  Point_2(segment.p2.getX(), segment.p2.getY()));

    const auto result = CGAL::intersection(ray, seg);

    if (result) {
        if (const Point_2* p = std::get_if<Point_2>(&*result)) {
            outX = p->x();
            outY = p->y();
            outDist = std::sqrt(CGAL::squared_distance(rayOrigin, *p));
            return true;
        }
    }
    return false;
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
 * Uses an angular sweep algorithm to determine visible portions of line segments
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

        // Find the closest intersection for this angle across all segments
        float closestDist;
        int closestLocationIndex = findClosestIntersection(currentAngle, closestDist);

        // If we found an intersection and it's different from the last segment
        addProjectionIfNeeded(projections, lastAngle, lastDepth, lastLocationIndex,
                             currentAngle, closestDist, closestLocationIndex);
    }

    // Close the last projection if any
    if (lastLocationIndex != -1 && lastAngle >= 0) {
        Colour color = Constants::GREEN;
        projections.emplace_back(lastAngle, lastDepth, lastAngle + 0.001f, lastDepth, color);
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
        
        for (const Line& line : area.sides) {
            float x1 = line.p1.getX();
            float y1 = line.p1.getY();
            float x2 = line.p2.getX();
            float y2 = line.p2.getY();
            
            // Calculate angles for both endpoints
            float angle1 = calculateRadians(x1, y1);
            float angle2 = calculateRadians(x2, y2);
            
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

// Finds the closest intersection for a given angle across all segments
int World::findClosestIntersection(double currentAngle, float& outDist) {
    const auto allLocs = allobjects.getLocations();
    float closestDist = std::numeric_limits<float>::infinity();
    int closestLocationIndex = -1;

    int locationIndex = 0;
    for (Location* loc : allLocs) {
        Rectangle area = loc->getArea();

        for (const Line& segment : area.sides) {
            float intersectX, intersectY, intersectDist;
            if (raySegmentIntersection(currentAngle, segment, intersectX, intersectY, intersectDist)) {
                if (intersectDist < closestDist) {
                    closestDist = intersectDist;
                    closestLocationIndex = locationIndex;
                }
            }
        }
        locationIndex++;
    }

    outDist = closestDist;
    return closestLocationIndex;
}

// Adds a projection if the location changed or angle threshold exceeded
void World::addProjectionIfNeeded(std::vector<Projection>& projections,
                                   float& lastAngle, float& lastDepth, int& lastLocationIndex,
                                   double currentAngle, float closestDist, int closestLocationIndex) {
    if (closestLocationIndex == -1) return;

    // If this is a new visible segment (different location or significant angle/depth change)
    if (lastLocationIndex != closestLocationIndex || lastAngle < 0 ||
        std::abs(currentAngle - lastAngle) > 0.001f) {

        // If we had a previous segment, close it and create a projection
        if (lastLocationIndex != -1 && lastAngle >= 0) {
            Colour color = Constants::GREEN; // Default color
            projections.emplace_back(lastAngle, lastDepth, currentAngle, closestDist, color);
        }

        // Start tracking this new visible segment
        lastAngle = currentAngle;
        lastDepth = closestDist;
        lastLocationIndex = closestLocationIndex;
    }
}

// Filters projections by the organism's field of view
std::vector<Projection> World::filterProjectionsByFOV(const std::vector<Projection>& projections) {
    std::vector<Projection> filteredProjections;
    double halfFOVrad = myOrgMan.field_of_view_rad / 2.0;
    double orgHeadingRad = heading_to_rad(myOrgMan.heading);
    double leftBound = normalize(orgHeadingRad + halfFOVrad);
    double rightBound = normalize(orgHeadingRad - halfFOVrad);

    // Simple clipping operation on the projections
    // TODO: not 100% correct for the case, when leftBound > rightBound (i.e. FOV crosses 0 rad)
    // TODO: not 100% correct for the case, when clipping occurs because the depth at the clipped edge is different
    for (const Projection& p : projections) {
        // Normal case
        if (p.startrad >= leftBound && p.endrad <= rightBound) {
            filteredProjections.push_back(p);
        } else if (p.startrad < leftBound && p.endrad <= rightBound) {
            Projection clippedProj(leftBound, p.startdepth, p.endrad, p.enddepth, p.color);
            filteredProjections.push_back(clippedProj);
        } else if (p.startrad >= leftBound && p.endrad > rightBound) {
            Projection clippedProj(p.startrad, p.startdepth, rightBound, p.enddepth, p.color);
            filteredProjections.push_back(clippedProj);
        } else if (p.startrad < leftBound && p.endrad > rightBound) {
            Projection clippedProj(leftBound, p.startdepth, rightBound, p.enddepth, p.color);
            filteredProjections.push_back(clippedProj);
        }
    }

    return filteredProjections;
}

