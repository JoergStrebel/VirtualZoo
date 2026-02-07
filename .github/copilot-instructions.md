# Copilot Instructions for VirtualZoo

## Project Overview
VirtualZoo is a C++17 simulator for growing artificially intelligent organisms in a 2D environment. The project uses:
- **CMake 3.28+** for build management
- **Google Test (GTest)** for unit testing
- **SDL2** for visualization
- **CGAL** for computational geometry
- **Boost** for utility functionality

**Key architectural docs:**
- [Organism Design](../organism_design.md) - Defines organism capabilities, sensors, and cognitive design principles
- [Computer Consciousness](../computer_consciousness.md) - Project motivation
- [Learning Algorithms](../learning_algorithms.md) - Reinforcement learning concepts used

## Build and Test Commands

### Build the Project
```bash
cd build
cmake ..
make
```

### Run the Main Simulator
```bash
./build/bin/simcore
```

### Run All Tests
```bash
cd build
ctest
```

### Run a Single Test
```bash
cd build
./organism_test           # Test organism-related functionality
./world_test              # Test world simulation and collision detection
```

### Run Tests with Verbose Output
```bash
cd build
ctest --verbose
# or run individual test directly:
./organism_test --gtest_filter="TestName.*"
```

### Build and Test in One Step
```bash
cd build && make && ctest --verbose
```

## High-Level Architecture

### Core Simulation Loop
- **World** (`world.h/cpp`) - Main simulator that manages the environment, handles collisions, and triggers organism updates
- **Organism** (`organism.h/cpp`) - Represents a single simulated creature with sensors, internal state, and actions
- **Organism_Manager** (`organism_manager.cpp`) - Handles organism behavior, sensory processing, and motor control
- **Locations** (`locations.h/cpp`) - Spatial indexing system for fast collision detection and object lookup

### Sensory System
- **Sensor** (`sensor.h/cpp`) - Base class for sensory inputs
- **Projection** (`Projection.h/cpp`) - Maps 3D world objects to 2D retina via pinhole camera model
- Organisms perceive the world through a limited symmetric field of view (default ~90°) mapped to a 1D retina with depth information

### Visualization
- **visualize** (`visualize.h/cpp`) - Base class for rendering backends
- **visualize_gui** (`visualize_gui.cpp`) - SDL2-based GUI implementation
- Visualization is intentionally separate from simulation logic; it does not affect physics or organism behavior

### Geometry and Spatial Computing
- **Geometric primitives** (`worldmodel/`): `Point.h/cpp`, `Line.h/cpp`, `Rectangle.h/cpp`
- Leverages CGAL for advanced computational geometry operations
- Angular sweep algorithm used for collision detection and visual perception computation

## Key Code Conventions

### Code Style & Practices
- **C++ Standard**: C++17 with strict compiler flags (`-Wall -Wextra -Wconversion` etc.)
- **Naming**: Classes use PascalCase, methods/variables use snake_case
- **Memory**: Prefer modern C++ patterns; Rule of 3/5 applies to classes with dynamic resources
- **Initialization**: Use value initialization `{}` instead of default initialization where possible
- **Compiler flags**: Built with `-march=native` for performance optimization

### Simulation Constants
- All configurable parameters are in `appconfig.h/cpp` and `constants.h`
- World grid resolution, organism sensor ranges, and energy mechanics are configured here
- Use `appconfig` singleton pattern for runtime configuration

### Testing with GTest
- Test files in `test/` directory named with `*_test.cpp` suffix
- Use `FRIEND_TEST` macro for white-box testing (see `world_test.cpp` which defines `UNIT_TEST` at compile time)
- Tests leverage the static library `simcore_lib` to avoid recompiling main
- New tests should follow GTest conventions: `TEST(TestClass, TestName)`

### Organization Principles
Following the design document, maintain separation of concerns:
- **Simulation** (world, organism, physics) is independent of **visualization** (GUI rendering)
- **Sensory processing** is physically realistic (pinhole cameras, limited FOV)
- **Organism learning** uses pluggable algorithms with consistent APIs
- **Distributed cognition**: Cognitive functions are modular and can operate asynchronously

### Geometric Coordinate System
- World uses standard 2D Cartesian coordinates (x, y)
- Organisms track position and orientation (heading)
- Organisms do NOT have built-in GPS or compass; they navigate via perception only
- Collision detection happens in world simulation, not visualization

## TODO Tracking
The project uses `TODO.md` for development priorities. High-priority items include:
- Implementing `World::create_visual_impression()` for sensory processing
- Adding unit tests for visual projection
- Implementing basic pattern recognition for organism behavior
- Decoupling visualization timing from simulation steps

## Important Notes
- **GPU/CPU Targets**: Compiled for Intel Westmere (or better) with SSE4.1/SSE4.2 support
- **Platform**: Tested on Linux; uses `-fsanitize=undefined` and `-ftrapv` for safety in debug builds
- **Dependencies**: Google Test, SDL2, SDL2_image, CGAL, and Boost are fetched/linked via CMake
