// SPDX-FileCopyrightText: 2023 Jörg Strebel <email>
// SPDX-License-Identifier: Apache-2.0

#include <gtest/gtest.h>
#include "world.h"
#include "depth_pixel.h"
#include "colour.h"
#include "constants.h"
#include <cmath>
#include <limits>

// World owns a fully-wired Organism (myOrg) and Organism_Manager (myOrgMan).
// Organism exposes private retina arrays to these tests via FRIEND_TEST.

static constexpr double EPS = 1e-6;

// Helper: make a DepthPixel with a visible object
static DepthPixel makePixel(double angle, double depth,
                             uint8_t r, uint8_t g, uint8_t b,
                             int locIdx = 0)
{
    DepthPixel px;
    px.angle = angle;
    px.depth = depth;
    px.location_index = locIdx;
    px.world_color.emplace(r, g, b, "test");
    return px;
}

// Helper: make a DepthPixel with no object visible
static DepthPixel makeEmptyPixel(double angle)
{
    DepthPixel px;
    px.angle = angle;
    px.depth = std::numeric_limits<double>::infinity();
    // location_index and world_color stay nullopt
    return px;
}

// Empty depth buffer: retina stays at default values
TEST(OrganismTest, VisualStimulus_EmptyBuffer_RetinaIsDefault) {
    World w;
    w.myOrg.visual_stimulus({});

    for (int i = 0; i < 90; ++i) {
        EXPECT_EQ(w.myOrg.retina_r[i], 0) << "retina_r[" << i << "]";
        EXPECT_EQ(w.myOrg.retina_g[i], 0) << "retina_g[" << i << "]";
        EXPECT_EQ(w.myOrg.retina_b[i], 0) << "retina_b[" << i << "]";
        EXPECT_NEAR(w.myOrg.retina_distance[i], Constants::UNLIMITEDSIGHTDISTANCE, EPS)
            << "retina_distance[" << i << "]";
    }
}

// A single depth pixel at the center of the FOV (heading = π) activates only
// the middle retina slots (43–46); edge slots stay at default.
// Threshold = π/ANGULAR_RESOLUTION ≈ 0.0314 rad; pixels 43–46 are within it.
TEST(OrganismTest, VisualStimulus_PixelAtCenter_MapsToMiddleRetina) {
    World w;
    // Default heading is π. Center of FOV = π.
    const auto px = makePixel(Constants::PI, 1.0, 100, 150, 200);
    w.myOrg.visual_stimulus({px});

    // Pixels 43–46 should carry the colour
    for (int i = 43; i <= 46; ++i) {
        EXPECT_EQ(w.myOrg.retina_r[i], 100) << "retina_r[" << i << "]";
        EXPECT_EQ(w.myOrg.retina_g[i], 150) << "retina_g[" << i << "]";
        EXPECT_EQ(w.myOrg.retina_b[i], 200) << "retina_b[" << i << "]";
    }
    // Edge pixels are outside the threshold and stay at 0
    EXPECT_EQ(w.myOrg.retina_r[0],  0);
    EXPECT_EQ(w.myOrg.retina_r[89], 0);
}

// Distance stored is sqrt(depth), not the raw squared value.
TEST(OrganismTest, VisualStimulus_CorrectDistanceSqrt) {
    World w;
    // depth = 25.0 → retina_distance should be 5.0
    const auto px = makePixel(Constants::PI, 25.0, 0, 255, 0);
    w.myOrg.visual_stimulus({px});

    for (int i = 43; i <= 46; ++i) {
        EXPECT_NEAR(w.myOrg.retina_distance[i], 5.0, EPS) << "i=" << i;
    }
}

// Pixel with no visible object: colour stays 0, distance stays UNLIMITEDSIGHTDISTANCE.
TEST(OrganismTest, VisualStimulus_NoObject_ColorStaysZero) {
    World w;
    const auto px = makeEmptyPixel(Constants::PI);
    w.myOrg.visual_stimulus({px});

    for (int i = 0; i < 90; ++i) {
        EXPECT_EQ(w.myOrg.retina_r[i], 0);
        EXPECT_EQ(w.myOrg.retina_g[i], 0);
        EXPECT_EQ(w.myOrg.retina_b[i], 0);
        EXPECT_NEAR(w.myOrg.retina_distance[i], Constants::UNLIMITEDSIGHTDISTANCE, EPS);
    }
}

// Zero-crossing heading: heading = 0, depth pixel at angle 0 maps to center
// retina slots (43–46) using the short-arc angular distance over the 0/2π wrap.
TEST(OrganismTest, VisualStimulus_ZeroCrossingHeading) {
    World w;
    w.myOrgMan.turn_around(-1, 0);  // rotates heading from π → 0
    // Depth pixel right at heading angle (0 rad)
    const auto px = makePixel(0.0, 16.0, 200, 100, 50);
    w.myOrg.visual_stimulus({px});

    // Centre retina pixels should carry the colour and sqrt(16)=4 distance
    for (int i = 43; i <= 46; ++i) {
        EXPECT_EQ(w.myOrg.retina_r[i], 200) << "i=" << i;
        EXPECT_NEAR(w.myOrg.retina_distance[i], 4.0, EPS) << "i=" << i;
    }
    // Edge pixel (right edge of FOV) stays at default
    EXPECT_EQ(w.myOrg.retina_r[0], 0);
}
