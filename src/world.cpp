// SPDX-FileCopyrightText: 2023 Jörg Strebel <email>
// SPDX-License-Identifier: Apache-2.0

#include "world.h"
#include "constants.h"
#include "sensor.h"
#include <cmath>
#include <limits>
#include <algorithm>
#include <CGAL/intersections.h>


World::World()
= default;

void World::run_world(){
    this->check_collisions();
    this->create_visual_impression();
    myOrg.act();
}

void World::check_collisions(){

    std::vector<Location*> allLocs = allobjects.getLocations();
    for(std::size_t i = 0; i < std::size(myOrg.sensorarray); ++i){
        const sensor& currentsens = myOrg.sensorarray[i];

        //Calculate effective world coordinates of sensor
        int x = static_cast<int>(std::round(myOrgMan.x)+static_cast<double>(Constants::ENTITYSIZE)/2.0+static_cast<double>(currentsens.x));
        int y = static_cast<int>(std::round(myOrgMan.y)+static_cast<double>(Constants::ENTITYSIZE)/2.0+static_cast<double>(currentsens.y));

        //check collision between organism and world boundaries
        if (x<=0 ||
            y<=0 ||
            y >= Constants::MAXY ||
            x >= Constants::MAXX) {
            //send stimulus to the organism
            myOrg.physical_stimulus(currentsens.get_id());
        }
        //check collision between the organism and locations
        for (Location* loc :allLocs){
            if (x>=loc->getTopLeft().getX() &&
                x<=loc->getBottomRight().getX() &&
                y >= loc->getTopLeft().getY() &&
                y <= loc->getBottomRight().getY()) {
            //send stimulus to the organism
                myOrg.physical_stimulus(currentsens.get_id());
            }
        }
    }
}

// Calculates the radians value of a point in the world relative to the organism's position
// 0.0 is heading west, pi/2 is heading north, pi is heading east, 3pi/2 is heading south
// counting is counterclockwise
double World::calculateRadians(double x, double y) const {
    return util.normalize(std::atan2(y - myOrgMan.y, x - myOrgMan.x));
}

// Helper function to calculate the squared distance between two points
double World::distanceSquared(const double x1, const double y1, const double x2, const double y2) {
    double dx = x2 - x1;
    double dy = y2 - y1;
    return dx * dx + dy * dy;
}


// Computes ray-line intersection with squared distance from organism position
bool World::rayLineIntersection(double rayAngle, const Line& line, double& outSquaredDistance) const {
    // Create a ray originating from the organism's position at the given angle
    CGAL_Point_2 rayOrigin(myOrgMan.x, myOrgMan.y);

    CGAL_Ray_2 ray(rayOrigin, CGAL_Direction_2(std::cos(rayAngle), std::sin(rayAngle)));

    // Get the line segment
    Point startPt = line.getStartPoint();
    Point endPt = line.getEndPoint();
    CGAL_Segment_2 segment(CGAL_Point_2(startPt.getX(), startPt.getY()),
                           CGAL_Point_2(endPt.getX(), endPt.getY()));

    // Compute intersection using CGAL
    auto intersection = CGAL::intersection(ray, segment);

    if (!intersection) {
        return false;
    }

    // Extract the intersection point
    const CGAL_Point_2* intersectionPoint = nullptr;
    if (const CGAL_Point_2* pt = std::get_if<CGAL_Point_2>(&*intersection)) {
        intersectionPoint = pt;
    } else {
        // If result is a segment (ray and line overlap), use the closer endpoint
        if (const CGAL_Segment_2* seg = std::get_if<CGAL_Segment_2>(&*intersection)) {
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
    std::vector<DepthPixel> depthBuffer(Constants::ANGULAR_RESOLUTION);
    for (auto& pixel : depthBuffer) {
        pixel.depth = std::numeric_limits<double>::infinity();
    }

    const auto allLocs = allobjects.getLocations();

    // Perform angular sweep: for each location, cast rays at each angular pixel
    // and update depth buffer with nearest intersection
    for (int pixelIdx = 0; pixelIdx < Constants::ANGULAR_RESOLUTION; ++pixelIdx) {
        // Calculate angle for this pixel: pixel * (2π / ANGULAR_RESOLUTION)
        double pixelAngle = (2.0 * Constants::PI / Constants::ANGULAR_RESOLUTION) * pixelIdx;
        depthBuffer[pixelIdx].angle = pixelAngle;

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
                        depthBuffer[pixelIdx].location_index = locationIndex;
                    }
                }
            }
            locationIndex++;
        }
    }
    for (auto& pixel : depthBuffer) {
        if (pixel.location_index.has_value()) {
            const Colour& c = allLocs[pixel.location_index.value()]->getColor();
            pixel.world_color.emplace(c.r, c.g, c.b, c.name);
        }
    }

    const std::vector<DepthPixel> culledDepthBuffer = trimDepthBufferByFOV(depthBuffer);

    // Hand over the buffer to the organism as a visual stimulus
    myOrg.visual_stimulus(culledDepthBuffer);
}

// trim the depth buffer to only include pixels within the organism's field of view (FOV)
std::vector<DepthPixel> World::trimDepthBufferByFOV(const std::vector<DepthPixel>& depthBuffer) const {
    std::vector<DepthPixel> trimmedBuffer;
    double leftBound, rightBound;
    myOrgMan.getFoV(leftBound, rightBound);

    //fill the trimmed buffer with the corresponding pixels from the original depth buffer
    for (int i = 0; i < Constants::ANGULAR_RESOLUTION; ++i) {
        const double pixelAngle = depthBuffer[i].angle;
        // Check if pixel angle is within FOV
        // two cases: FOV does not cross 0 radians, FOV crosses 0 radians
        bool zeroCrossing = leftBound < Organism_Manager::field_of_view_rad; // heading is to the right, FoV crosses 0
        bool inFOV = zeroCrossing ? (
            (pixelAngle <= leftBound && pixelAngle >=0) || (pixelAngle >= rightBound && pixelAngle <= 2* Constants::PI)) :
            (pixelAngle <= leftBound && pixelAngle >= rightBound);

        if (inFOV) {
            trimmedBuffer.emplace_back(depthBuffer[i]);
        }
    }
    return trimmedBuffer;

}