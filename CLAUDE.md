# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Build

```bash
mkdir build && cd build && cmake .. && make -j$(nproc)
```

SDL and SDL_image must be soft-linked into the repo root (see README). CGAL is installed via the system package manager.

The build type is set to `Release` in CMakeLists.txt. Debug builds require changing `CMAKE_BUILD_TYPE`. UBSan (`-fsanitize=undefined`) and `-ftrapv` are always active — keep that in mind when interpreting crashes.

## Tests

```bash
# Run all tests
cd build && ctest --output-on-failure

# Run a specific test binary directly
./build/Release/organism_test
./build/Release/world_test

# Run a single test case by name
./build/Release/world_test --gtest_filter="WorldTest.RaySegmentIntersection_Hit"
```

Tests use Google Test. Private methods and members are exposed to tests via `FRIEND_TEST` macros guarded by `#ifdef UNIT_TEST`. The `UNIT_TEST` preprocessor define must be set in `CMakeLists.txt` via `target_compile_definitions`. Both test targets also need `CGAL::CGAL` linked explicitly.

## Architecture

The simulation has a single-organism, single-world structure. `World` owns one `Organism_Manager`, one `Organism`, and a `Locations` container. Each simulation tick calls `World::run_world()`, which does three things in order:

1. **Collision detection** (`check_collisions`): Checks each of the organism's 8 perimeter pressure sensors against world boundaries and all `Location` rectangles. Sends `physical_stimulus()` events to the organism for any hit sensor.

2. **Visual perception** (`create_visual_impression`): Casts 100 rays (one per angular pixel at `2π/100` spacing) against all `Location` line segments using CGAL. Builds a 100-entry `DepthPixel` depth buffer, trims it to the organism's 90° FOV, and delivers it to `Organism::visual_stimulus()`.

3. **Organism action** (`Organism::act`): The organism evaluates its stimuli and moves — currently collision-avoidance only (turn away + step forward). Visual processing in `recognize()` is a stub.

### Class responsibilities

- **`Organism_Manager`** mediates between `World` and `Organism` for all positional state: (x, y), heading (radians, 0 = right, increasing counterclockwise), step size (2.0 units), and FOV bounds. The organism itself never reads or writes position directly.

- **`Organism`** holds the sensor array, retina arrays (90 × RGB `uint8_t` + distance `double`), and energy. It calls back into `Organism_Manager` for movement (`move()`, `turn_around()`).

- **`DepthPixel`** is the data transfer struct from `World` to `Organism`. `depth` is *squared* distance; `Organism::visual_stimulus()` stores `sqrt(depth)` in `retina_distance`. `world_color` and `location_index` are `std::optional` — absent means no object was hit by that ray.

- **`worldmodel/`** contains CGAL-backed geometric primitives (`Point`, `Line`, `Rectangle`). `Rectangle::getSides()` returns the 4 `Line` segments used for ray intersection.

### Angle conventions

- Angles are in radians, `[0, 2π)`, counterclockwise from the positive x-axis (east = 0, north = π/2, west = π, south = 3π/2).
- The depth buffer covers the full 360° (100 pixels). The FOV trim (`trimDepthBufferByFOV`) handles the zero-crossing case where the FOV spans the 0-radian boundary.
- Retina pixel 0 is the right (clockwise) edge of the FOV; pixel 89 is the left edge. The mapping uses nearest-neighbor with a threshold of `π / ANGULAR_RESOLUTION` to prevent a single depth pixel from flooding the entire retina.

### Key constants (`src/constants.h`)

| Constant | Value | Meaning |
|---|---|---|
| `MAXX`, `MAXY` | 640 | World dimensions (pixels) |
| `ENTITYSIZE` | 32 | Entity/tile size |
| `ANGULAR_RESOLUTION` | 100 | Depth buffer width (rays cast) |
| `PI` | 3.141592 | Used throughout |
| `UNLIMITEDSIGHTDISTANCE` | -1.0 | Sentinel for "no object" in retina_distance |
| `field_of_view_rad` | π/2 | 90° FOV (on `Organism_Manager`) |
