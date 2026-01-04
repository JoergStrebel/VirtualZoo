#include <gtest/gtest.h>
#include "world.h"
#include "worldmodel/Line.h"
#include "worldmodel/Point.h"
#include "constants.h"

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
static const double EPS = 1e-6;

TEST(WorldTest, CalculateRadians_Basic) {
    World w;
    // Setze Beobachter bei Ursprung
    w.myOrgMan.x = 0.0;
    w.myOrgMan.y = 0.0;

    // Punkt auf +X-Achse -> atan2(0,1) == 0
    EXPECT_NEAR(w.calculateRadians(1.0f, 0.0f), 0.0, EPS);
    // Punkt auf +Y-Achse -> atan2(1,0) == pi/2
    EXPECT_NEAR(w.calculateRadians(0.0f, 1.0f), Constants::PI/2.0, EPS);
}

TEST(WorldTest, DistanceSquared_Basic) {
    World w;
    double d = w.distanceSquared(1.0f, 2.0f, 4.0f, 4.0f); // dx=3, dy=2 -> 9+4=13
    EXPECT_NEAR(d, 13.0, EPS);
}

TEST(WorldTest, Normalize_Basic) {
    World w;
    double res = World::normalize(-Constants::PI/2.0);
    // -pi/2 normalized -> 3*pi/2
    EXPECT_NEAR(res, 3.0 * Constants::PI / 2.0, EPS);

    // value already in [0,2pi) unchanged
    double val = World::normalize(Constants::PI);
    EXPECT_NEAR(val, Constants::PI, EPS);
}

TEST(WorldTest, HeadingToRad_Basic) {
    World w;
    // Per implementation: heading 0 => maps to north => pi/2
    double rad = World::heading_to_rad(0.0);
    EXPECT_NEAR(rad, Constants::PI/2.0, EPS);

    // heading 90 -> east -> 0 rad after conversion and normalize
    double rad90 = World::heading_to_rad(90.0);
    EXPECT_NEAR(rad90, 0.0, EPS);
}

TEST(WorldTest, RaySegmentIntersection_Hit) {
    World w;
    // Observer at origin
    w.myOrgMan.x = 0.0;
    w.myOrgMan.y = 0.0;

    // Segment vertical at x=5 from y=-1..1
    Point p1(5.0, -1.0);
    Point p2(5.0, 1.0);
    Line seg(p1, p2);

    float outX = 0, outY = 0, outDist = 0;
    bool hit = w.raySegmentIntersection(0.0f /* angle 0 => +X axis */, seg, outX, outY, outDist);
    ASSERT_TRUE(hit);
    EXPECT_NEAR(outX, 5.0, 1e-4);
    EXPECT_NEAR(outY, 0.0, 1e-4);
    EXPECT_NEAR(outDist, 5.0, 1e-4);
}

TEST(WorldTest, RaySegmentIntersection_Miss) {
    World w;
    w.myOrgMan.x = 0.0;
    w.myOrgMan.y = 0.0;

    // Segment behind observer (x = -5), ray points to +X
    Point p1(-5.0, -1.0);
    Point p2(-5.0, 1.0);
    Line seg(p1, p2);

    float outX = 0, outY = 0, outDist = 0;
    bool hit = w.raySegmentIntersection(0.0f /* angle 0 => +X axis */, seg, outX, outY, outDist);
    EXPECT_FALSE(hit);
}

