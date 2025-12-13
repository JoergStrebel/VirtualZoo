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

// Helper function to calculate the squared distance between two points
float World::distanceSquared(float x1, float y1, float x2, float y2) const {
    float dx = x2 - x1;
    float dy = y2 - y1;
    return dx * dx + dy * dy;
}

// Helper function to find ray-segment intersection
// Returns true if intersection exists, and sets intersection point and distance
bool World::raySegmentIntersection(float rayAngle, const Line& segment, 
                                   float& outX, float& outY, float& outDist) const {
    float observerX = myOrgMan.x;
    float observerY = myOrgMan.y;
    
    // Ray direction
    float rayDirX = std::cos(rayAngle);
    float rayDirY = std::sin(rayAngle);
    
    // Segment endpoints
    float x1 = segment.p1.getX();
    float y1 = segment.p1.getY();
    float x2 = segment.p2.getX();
    float y2 = segment.p2.getY();
    
    // Segment direction
    float segDirX = x2 - x1;
    float segDirY = y2 - y1;
    
    // Solve the parametric equations:
    // observerX + t * rayDirX = x1 + u * segDirX
    // observerY + t * rayDirY = y1 + u * segDirY
    // where t >= 0 and 0 <= u <= 1
    
    float denominator = rayDirX * segDirY - rayDirY * segDirX;
    
    // Lines are parallel
    if (std::abs(denominator) < 1e-10) {
        return false;
    }
    
    float dx = x1 - observerX;
    float dy = y1 - observerY;
    
    float u = (rayDirX * dy - rayDirY * dx) / denominator;
    float t = (segDirX * dy - segDirY * dx) / denominator;
    
    // Check if intersection is valid
    if (t >= 0 && u >= 0 && u <= 1) {
        outX = observerX + t * rayDirX;
        outY = observerY + t * rayDirY;
        outDist = t;
        return true;
    }
    
    return false;
}

// Structure to represent an angle event in the angular sweep
struct AngleEvent {
    float angle;
    const Line* segment;
    int locationIndex;  // To track which location this segment belongs to
    bool isEndpoint;    // True if this is an actual endpoint, false if it's an offset ray
    
    // Constructor
    AngleEvent(float a, const Line* seg, int locIdx, bool isEnd = true) 
        : angle(a), segment(seg), locationIndex(locIdx), isEndpoint(isEnd) {}
};

/* Render the locations in the world as a visual impression for the organism
 * Uses an angular sweep algorithm to determine visible portions of line segments
 */
void World::create_visual_impression(){
    auto allLocs = allobjects.getLocations();
    std::vector<Projection> projections;
    std::vector<AngleEvent> angleEvents;
    
    // Collect all line segments and create angle events
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
            
            // Add slightly offset angles to handle edge cases
            const float epsilon = 0.0001f;
            angleEvents.emplace_back(angle1 - epsilon, &line, locationIndex, false);
            angleEvents.emplace_back(angle1 + epsilon, &line, locationIndex, false);
            angleEvents.emplace_back(angle2 - epsilon, &line, locationIndex, false);
            angleEvents.emplace_back(angle2 + epsilon, &line, locationIndex, false);
        }
        locationIndex++;
    }
    
    // Sort events by angle
    std::sort(angleEvents.begin(), angleEvents.end(), 
              [](const AngleEvent& a, const AngleEvent& b) {
                  return a.angle < b.angle;
              });
    
    // Perform angular sweep
    float lastAngle = -1.0f;
    float lastDepth = -1.0f;
    int lastLocationIndex = -1;
    
    for (const auto& event : angleEvents) {
        float currentAngle = event.angle;
        
        // Normalize angle to [0, 2*PI)
        while (currentAngle < 0) currentAngle += 2.0 * Constants::PI;
        while (currentAngle >= 2.0 * Constants::PI) currentAngle -= ((double)2.0) * Constants::PI;
        
        // Find the closest intersection for this angle across all segments
        float closestDist = std::numeric_limits<float>::infinity();
        int closestLocationIndex = -1;
        
        locationIndex = 0;
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
        
        // If we found an intersection and it's different from the last segment
        if (closestLocationIndex != -1) {
            // If this is a new visible segment (different location or significant angle/depth change)
            if (lastLocationIndex != closestLocationIndex || lastAngle < 0 ||
                std::abs(currentAngle - lastAngle) > 0.001f) {
                
                // If we had a previous segment, close it and create a projection
                if (lastLocationIndex != -1 && lastAngle >= 0) {
                    // Get the color of the previous location
                    int color = 0; // Default color
                    if (lastLocationIndex >= 0 && lastLocationIndex < (int)allLocs.size()) {
                        // You may need to add a method to get color from Location
                        // For now, using locationIndex as a simple color identifier
                        color = lastLocationIndex;
                    }
                    
                    projections.emplace_back(lastAngle, lastDepth, currentAngle, closestDist, color);
                }
                
                // Start tracking this new visible segment
                lastAngle = currentAngle;
                lastDepth = closestDist;
                lastLocationIndex = closestLocationIndex;
            }
        }
    }
    
    // Close the last projection if any
    if (lastLocationIndex != -1 && lastAngle >= 0) {
        int color = lastLocationIndex;
        // Close with a small angle increment
        projections.emplace_back(lastAngle, lastDepth, lastAngle + 0.001f, lastDepth, color);
    }
    
    // Hand over the projections to the organism as a visual stimulus
    // Always hand over, even if vector is empty --> nothing to be seen
    myOrg.visual_stimulus(projections);
}

