// SPDX-FileCopyrightText: 2023 Jörg Strebel <email>
// SPDX-License-Identifier: Apache-2.0

#include "world.h"
#include "constants.h"
#include "sensor.h"
#include <cmath>
#include <limits>
#include <algorithm>
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
        int x = static_cast<int>(std::round(myOrgMan.x)+Constants::ENTITYSIZE/2.0+currentsens->x);
        int y = static_cast<int>(std::round(myOrgMan.y)+Constants::ENTITYSIZE/2.0+currentsens->y);
        
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

// Computes ray-line intersection with squared distance from organism position
bool World::rayLineIntersection(double rayAngle, const Line& line, double& outSquaredDistance) const {
    // Create a ray originating from the organism's position at the given angle
    Point_2 rayOrigin(myOrgMan.x, myOrgMan.y);

    // Ray direction: cos(angle) for x, sin(angle) for y
    double rayDirX = std::cos(rayAngle);
    double rayDirY = std::sin(rayAngle);

    Ray_2 ray(rayOrigin, K::Direction_2(rayDirX, rayDirY));

    // Get the line segment
    Point startPt = line.getStartPoint();
    Point endPt = line.getEndPoint();
    Segment_2 segment(CGAL_Point_2(startPt.getX(), startPt.getY()),
                     CGAL_Point_2(endPt.getX(), endPt.getY()));

    // Compute intersection using CGAL
    auto intersection = CGAL::intersection(ray, segment);

    if (!intersection) {
        return false;
    }

    // Extract the intersection point
    const Point_2* intersectionPoint = nullptr;
    if (const Point_2* pt = std::get_if<Point_2>(&*intersection)) {
        intersectionPoint = pt;
    } else {
        // If result is a segment (ray and line overlap), use the closer endpoint
        if (const Segment_2* seg = std::get_if<Segment_2>(&*intersection)) {
            intersectionPoint = &seg->point(0);
        } else {
            return false;
        }
    }

    // Calculate squared distance from ray origin to intersection point
    double dx = intersectionPoint->x() - myOrgMan.x;
    double dy = intersectionPoint->y() - myOrgMan.y;
    outSquaredDistance = dx * dx + dy * dy;

    return true;
}

/* Render the locations in the world as a visual impression for the organism
 * Uses an angular sweep algorithm with a depth buffer to determine visible portions of lines in the world
 * The depth buffer has ANGULAR_RESOLUTION (100) angular pixels, each representing a slice of 2π/100 radians
 */
void World::create_visual_impression(){
    // Initialize depth buffer: 100 pixels, each representing 2π/100 radians
    const std::vector<DepthPixel> depthBuffer(Constants::ANGULAR_RESOLUTION);
    for (auto& pixel : depthBuffer) {
        pixel.depth = std::numeric_limits<double>::infinity();
        pixel.locationIndex = -1;  // -1 means no object
    }

    const auto allLocs = allobjects.getLocations();

    // Perform angular sweep: for each location, cast rays at each angular pixel
    // and update depth buffer with nearest intersection
    for (int pixelIdx = 0; pixelIdx < Constants::ANGULAR_RESOLUTION; ++pixelIdx) {
        // Calculate angle for this pixel: pixel * (2π / ANGULAR_RESOLUTION)
        double pixelAngle = (2.0 * Constants::PI / Constants::ANGULAR_RESOLUTION) * pixelIdx;

        // Test intersection with all line segments from all locations
        int locationIndex = 0;
        for (Location* loc : allLocs) {
            Rectangle area = loc->getArea();
            auto sides = area.getSides();

            for (const Line& line : sides) {
                double squaredDistance = 0.0;
                if (rayLineIntersection(pixelAngle, line, squaredDistance)) {
                    // Update depth buffer if this is closer than current entry
                    if (squaredDistance < depthBuffer[pixelIdx].depth) {
                        depthBuffer[pixelIdx].depth = squaredDistance;
                        depthBuffer[pixelIdx].locationIndex = locationIndex;
                    }
                }
            }
            locationIndex++;
        }
    }
    // trim the depth buffer to only include pixels within the organism's field of view (FOV)
    const std::vector<DepthPixel> culledDepthBuffer = trimDepthBufferByFOV(depthBuffer);

    // Hand over the projections to the organism as a visual stimulus
    myOrg.visual_stimulus(depthBuffer);
}

std::vector<DepthPixel> World::trimDepthBufferByFOV(const std::vector<DepthPixel>) const {

}