# 2D Visibility Algorithm Implementation

## Overview

This document describes the angular sweep visibility algorithm implemented in `world.cpp` for determining which parts of
line segments are visible from a specific viewpoint in a 2D world.

## Algorithm: Angular Sweep

The algorithm uses an **angular sweep** approach to efficiently compute visible portions of line segments from the
organism's position.

### Key Concept

The algorithm sweeps rays in angular order around the observer position (360 degrees), and for each ray direction,
determines which line segment (if any) is closest to the observer.

### Algorithm Steps

1. **Event Generation** (Lines 140-166)
    - For each line segment endpoint, calculate its angle relative to the observer
    - Create angle events for:
        - Both endpoints of each segment
        - Slightly offset angles (±ε) to handle edge cases where rays pass exactly through endpoints

2. **Event Sorting** (Lines 168-172)
    - Sort all angle events by their angular value
    - This creates an ordered sequence of rays to cast

3. **Angular Sweep** (Lines 174-235)
    - For each angle in sorted order:
        - Cast a ray from the observer in that direction
        - Find the closest intersection with all line segments
        - Track which segment is visible at this angle

4. **Projection Generation** (Lines 203-228)
    - When the visible segment changes (different location), create a Projection
    - Each Projection contains:
        - `startrad`: Starting angle of the visible segment
        - `startdepth`: Distance at the start angle
        - `endrad`: Ending angle of the visible segment
        - `enddepth`: Distance at the end angle
        - `color`: Location identifier for rendering

5. **Visual Stimulus** (Lines 230-233)
    - Pass the generated projections to the organism's visual system

## Helper Functions

### `raySegmentIntersection()` (Lines 71-115)

Uses parametric line equations to find ray-segment intersections:

- Ray: `P = observer + t * direction` (where t ≥ 0)
- Segment: `Q = p1 + u * (p2 - p1)` (where 0 ≤ u ≤ 1)
- Solves the system to find intersection point and distance

### `calculateRadians()` (Lines 52-62)

Converts world coordinates to angular position relative to observer:

- Uses `atan2()` for correct quadrant handling
- Normalizes to [0, 2π) range
- 0.0 = west, π/2 = north, π = east, 3π/2 = south

### `distanceSquared()` (Lines 64-69)

Computes squared Euclidean distance (avoids expensive sqrt operation).

## Complexity Analysis

- **Time Complexity**: O(n² log n)
    - O(n log n) for sorting events (n = number of line segments)
    - O(n) events, each requiring O(n) intersection tests
    - Can be optimized to O(n² ) with spatial data structures

- **Space Complexity**: O(n)
    - Storage for angle events and projections

## Advantages

1. **Correctness**: Handles all edge cases including:
    - Overlapping segments
    - Segments at same angle but different distances
    - Partial occlusion

2. **Generality**: Works with arbitrary line segments, not just axis-aligned rectangles

3. **Precision**: Uses CGAL geometric primitives for robust calculations

## Potential Optimizations

1. **View Frustum Culling**: Pre-filter segments outside the organism's field of view
2. **Spatial Indexing**: Use a quad-tree or BSP tree to reduce intersection tests
3. **Incremental Updates**: Maintain active segment list and update incrementally
4. **Back-face Culling**: Skip segments facing away from the observer (requires surface normals)

## Usage Example

The algorithm is automatically called during each world update cycle:

```cpp
void World::run_world() {
    this->check_collisions();
    this->create_visual_impression();  // Visibility algorithm runs here
    myOrg.act();
}
```

The resulting `Projection` objects are passed to the organism's visual system for further processing.

## References

- Computational Geometry: Algorithms and Applications (de Berg et al.)
- Real-Time Rendering (Akenine-Möller et al.)
- Visibility Algorithms in Computer Graphics (Durand)
