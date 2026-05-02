// SPDX-FileCopyrightText: 2023 Jörg Strebel <email>
// SPDX-License-Identifier: Apache-2.0

#ifndef WORLD_H
#define WORLD_H


#include "locations.h"
#include "organism.h"
#include "organism_manager.h"
#include "depth_pixel.h"

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
    sim_util util;
    //checks collisions among objects and between objects and boundary
    //sends events to the affected objects, so that they can react on.
    void check_collisions();
    //calculates the radians value of a point in the world relative to the organism's position
    [[nodiscard]] double calculateRadians(double x, double y) const;

     //calculates squared distance between two points
    static double distanceSquared(double x1, double y1, double x2, double y2);

     //supplies the organism with a world view
    void create_visual_impression();

     // Depth buffer and projection building
    std::vector<DepthPixel> trimDepthBufferByFOV(const std::vector<DepthPixel>& depthBuffer) const;

    /**
     * Computes the ray-based squared distance intersection between a ray at a given angle
     * and a line segment. Returns true if intersection exists, false otherwise.
     */
    [[nodiscard]] bool rayLineIntersection(double rayAngle, const Line& line, double& outSquaredDistance) const;

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
