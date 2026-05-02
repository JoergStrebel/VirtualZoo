#include <gtest/gtest.h>
#include "world.h"
#include "worldmodel/Line.h"
#include "worldmodel/Point.h"
#include "constants.h"
#include <algorithm>
#include <limits>

// Hinweis zum CGAL-Handling:
// Die Projektquelle verwendet CGAL (Exact_predicates_inexact_constructions_kernel)
// als geometrische Grundlage für Point/Line. Die Tests verwenden die
// bereits vorhandenen Wrapper-Klassen `Point` und `Line`, die CGAL intern nutzen.
// Beim Bauen der Tests stellt CMake sicher, dass CGAL gefunden und gelinkt wird
// (siehe CMakeLists.txt: target_link_libraries(world_test CGAL::CGAL)).
// Es sind daher keine weiteren CGAL-spezifischen Schritte im Testcode nötig.

// Die World-Klasse gewährt den Tests Zugriff auf private Member via FRIEND_TEST
// (Option A). Daher können wir private Hilfsfunktionen direkt aufrufen.

// Toleranz für Fließkomma-Vergleiche
static constexpr double EPS = 1e-6;

TEST(WorldTest, CalculateRadians_Basic) {
    World w;
    // Setze Beobachter bei Ursprung
    w.myOrgMan.x = 0.0;
    w.myOrgMan.y = 0.0;

    // Punkt auf +X-Achse -> atan2(0,1) == 0
    EXPECT_NEAR(w.calculateRadians(1.0, 0.0), 0.0, EPS);
    // Punkt auf +Y-Achse -> atan2(1,0) == pi/2
    EXPECT_NEAR(w.calculateRadians(0.0, 1.0), Constants::PI/2.0, EPS);
}

TEST(WorldTest, DistanceSquared_Basic) {
    World w;
    double d = w.distanceSquared(1.0, 2.0, 4.0, 4.0); // dx=3, dy=2 -> 9+4=13
    EXPECT_NEAR(d, 13.0, EPS);
}

TEST(WorldTest, Normalize_Basic) {
    World w;
    sim_util util;
    double res = util.normalize(-Constants::PI/2.0);
    // -pi/2 normalized -> 3*pi/2
    EXPECT_NEAR(res, 3.0 * Constants::PI / 2.0, EPS);

    // value already in [0,2pi) unchanged
    double val = util.normalize(Constants::PI);
    EXPECT_NEAR(val, Constants::PI, EPS);
}


TEST(WorldTest, RaySegmentIntersection_Hit) {
    World w;
    // Observer at origin
    w.myOrgMan.x = 0.0;
    w.myOrgMan.y = 0.0;

    // Segment vertical at x=5 from y=-1..1
    Point p1(5.0, -1.0); //TODO
    Point p2(5.0, 1.0);
    Line seg(p1, p2);

    double outSquaredDist = 0;
    bool hit = w.rayLineIntersection(0.0 /* angle 0 => +X axis */, seg, outSquaredDist);
    ASSERT_TRUE(hit);
    // Intersection at (5, 0), so squared distance should be 25
    EXPECT_NEAR(outSquaredDist, 25.0, 1e-4);
}

// Build the canonical 100-pixel angular buffer (same layout as create_visual_impression)
static std::vector<DepthPixel> makeBuffer() {
    std::vector<DepthPixel> buf(Constants::ANGULAR_RESOLUTION);
    for (int i = 0; i < Constants::ANGULAR_RESOLUTION; ++i) {
        buf[i].angle = (2.0 * Constants::PI / Constants::ANGULAR_RESOLUTION) * i;
        buf[i].depth = std::numeric_limits<double>::infinity();
    }
    return buf;
}

static bool containsAngle(const std::vector<DepthPixel>& buf, double target) {
    return std::any_of(buf.begin(), buf.end(),
        [target](const DepthPixel& p){ return std::abs(p.angle - target) < 1e-9; });
}

TEST(WorldTest, RaySegmentIntersection_Miss) {
    World w;
    w.myOrgMan.x = 0.0;
    w.myOrgMan.y = 0.0;

    // Segment behind observer (x = -5), ray points to +X
    Point p1(-5.0, -1.0);
    Point p2(-5.0, 1.0);
    Line seg(p1, p2);

    double outSquaredDist = 0;
    bool hit = w.rayLineIntersection(0.0 /* angle 0 => +X axis */, seg, outSquaredDist);
    EXPECT_FALSE(hit);
}

// trimDepthBufferByFOV — heading PI (default), FOV = [3π/4, 5π/4], no zero-crossing

TEST(WorldTest, TrimDepthBuffer_NoZeroCrossing_CenterAngle_IsIncluded) {
    World w;
    const auto buf = makeBuffer();
    const auto trimmed = w.trimDepthBufferByFOV(buf);
    // buf[50].angle = 50 * 2π/100 ≈ π, the exact FOV centre for heading π
    EXPECT_TRUE(containsAngle(trimmed, buf[50].angle));
}

TEST(WorldTest, TrimDepthBuffer_NoZeroCrossing_AngleZero_IsExcluded) {
    World w;
    const auto buf = makeBuffer();
    const auto trimmed = w.trimDepthBufferByFOV(buf);
    EXPECT_FALSE(containsAngle(trimmed, buf[0].angle));  // 0 is outside [3π/4, 5π/4]
}

TEST(WorldTest, TrimDepthBuffer_NoZeroCrossing_BoundaryAngles_AreIncluded) {
    World w;
    const auto buf = makeBuffer();
    const auto trimmed = w.trimDepthBufferByFOV(buf);
    // buf[38].angle ≈ 2.388 > 3π/4 ≈ 2.356 — just inside the lower bound
    EXPECT_TRUE(containsAngle(trimmed, buf[38].angle));
    // buf[62].angle ≈ 3.896 < 5π/4 ≈ 3.927 — just inside the upper bound
    EXPECT_TRUE(containsAngle(trimmed, buf[62].angle));
}

TEST(WorldTest, TrimDepthBuffer_NoZeroCrossing_CorrectCount) {
    World w;
    const auto buf = makeBuffer();
    const auto trimmed = w.trimDepthBufferByFOV(buf);
    // FOV = π/2 out of 2π → 25 of 100 angular pixels (indices 38..62)
    EXPECT_EQ(trimmed.size(), 25u);
}

// trimDepthBufferByFOV — heading ≈ 0 (turn_around from π), FOV = [7π/4, π/4], zero-crossing

TEST(WorldTest, TrimDepthBuffer_ZeroCrossing_AngleZero_IsIncluded) {
    World w;
    w.myOrgMan.turn_around(-1, 0);  // rotates heading from π to ≈ 0
    const auto buf = makeBuffer();
    const auto trimmed = w.trimDepthBufferByFOV(buf);
    EXPECT_TRUE(containsAngle(trimmed, buf[0].angle));   // 0 is inside [7π/4, 2π) ∪ [0, π/4]
}

TEST(WorldTest, TrimDepthBuffer_ZeroCrossing_AnglePI_IsExcluded) {
    World w;
    w.myOrgMan.turn_around(-1, 0);
    const auto buf = makeBuffer();
    const auto trimmed = w.trimDepthBufferByFOV(buf);
    EXPECT_FALSE(containsAngle(trimmed, buf[50].angle)); // ≈ π is opposite the heading
}

TEST(WorldTest, TrimDepthBuffer_ZeroCrossing_BoundaryAngles_AreIncluded) {
    World w;
    w.myOrgMan.turn_around(-1, 0);
    const auto buf = makeBuffer();
    const auto trimmed = w.trimDepthBufferByFOV(buf);
    // buf[12].angle ≈ 0.754 < π/4 ≈ 0.785 — just inside the upper side of the FOV
    EXPECT_TRUE(containsAngle(trimmed, buf[12].angle));
    // buf[88].angle ≈ 5.529 > 7π/4 ≈ 5.498 — just inside the lower side of the FOV
    EXPECT_TRUE(containsAngle(trimmed, buf[88].angle));
}

TEST(WorldTest, TrimDepthBuffer_ZeroCrossing_AngleOutsideFOV_IsExcluded) {
    World w;
    w.myOrgMan.turn_around(-1, 0);
    const auto buf = makeBuffer();
    const auto trimmed = w.trimDepthBufferByFOV(buf);
    // buf[13].angle ≈ 0.817 > π/4 ≈ 0.785 — just outside the upper side
    EXPECT_FALSE(containsAngle(trimmed, buf[13].angle));
    // buf[87].angle ≈ 5.467 < 7π/4 ≈ 5.498 — just outside the lower side
    EXPECT_FALSE(containsAngle(trimmed, buf[87].angle));
}

TEST(WorldTest, TrimDepthBuffer_ZeroCrossing_CorrectCount) {
    World w;
    w.myOrgMan.turn_around(-1, 0);
    const auto buf = makeBuffer();
    const auto trimmed = w.trimDepthBufferByFOV(buf);
    // FOV = π/2: indices 0..12 (13 pixels) + indices 88..99 (12 pixels) = 25 total
    EXPECT_EQ(trimmed.size(), 25u);
}

