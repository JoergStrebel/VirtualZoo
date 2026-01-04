// SPDX-FileCopyrightText: 2023 Jörg Strebel <email>
// SPDX-License-Identifier: Apache-2.0

#ifndef WORLD_H
#define WORLD_H

#include <string>
#include "locations.h"
#include "organism.h"
#include "organism_manager.h"

// Structure to represent an angle event in the angular sweep
struct AngleEvent {
    float angle;
    const Line* segment; //TODO: not used anywhere - verify logic
    int locationIndex;  // To track which location this segment belongs to
    bool isEndpoint;    // True if this is an actual endpoint, false if it's an offset ray

    // Constructor
    AngleEvent(const float a, const Line* seg, const int locIdx, const bool isEnd = true)
        : angle(a), segment(seg), locationIndex(locIdx), isEndpoint(isEnd) {}
};

/**
 * This class represents the simulated world.
 */
class World
{
public:     
     /**
     * Default constructor
     */
    World();
    void run_world();

    Locations allobjects;
    Organism_Manager myOrgMan;
    Organism myOrg{"beetle", myOrgMan};    
    
private:
    //checks collisions among objects and between objects and boundary
    //sends events to the affected objects, so that they can react on.
    void check_collisions();
    //calculates the radians value of a point in the world relative to the organism's position
    float calculateRadians(float x, float y) const;

     //calculates squared distance between two points
    static float distanceSquared(float x1, float y1, float x2, float y2);
    //finds intersection between a ray and a line segment
    bool rayLineIntersection(float rayAngle, const Line& line,
                               float& outX, float& outY, float& outDist) const;
    static double normalize(double radvalue);
    static double heading_to_rad(double heading);
     //supplies the organism with a world view
    void create_visual_impression();

    // Helper functions for create_visual_impression refactoring
    void collectAngleEvents(std::vector<AngleEvent>& angleEvents);
    int findClosestIntersection(double currentAngle, float& outDist);
    void addProjectionIfNeeded(std::vector<Projection>& projections,
                               float& lastAngle, float& lastDepth, int& lastLocationIndex,
                               double currentAngle, float closestDist, int closestLocationIndex);
    std::vector<Projection> filterProjectionsByFOV(const std::vector<Projection>& projections);

#ifdef UNIT_TEST
#include <gtest/gtest.h>
#endif

#ifdef UNIT_TEST
    // Grant test access to private methods (Option A)
    // Unit tests rely on FRIEND_TEST to access private helpers.
    friend class ::testing::Test; // ensure google test symbols available
    // Specific friend test declarations
    FRIEND_TEST(WorldTest, CalculateRadians_Basic);
    FRIEND_TEST(WorldTest, DistanceSquared_Basic);
    FRIEND_TEST(WorldTest, Normalize_Basic);
    FRIEND_TEST(WorldTest, HeadingToRad_Basic);
    FRIEND_TEST(WorldTest, RaySegmentIntersection_Hit);
    FRIEND_TEST(WorldTest, RaySegmentIntersection_Miss);
#endif
};

#endif // WORLD_H
