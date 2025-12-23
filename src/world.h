// SPDX-FileCopyrightText: 2023 Jörg Strebel <email>
// SPDX-License-Identifier: Apache-2.0

#ifndef WORLD_H
#define WORLD_H

#include <string>
#include "locations.h"
#include "organism.h"
#include "organism_manager.h"

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
    bool raySegmentIntersection(float rayAngle, const Line& segment, 
                               float& outX, float& outY, float& outDist) const;
    static double normalize(double radvalue);
    static double heading_to_rad(double heading);
     //supplies the organism with a world view
    void create_visual_impression();

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
