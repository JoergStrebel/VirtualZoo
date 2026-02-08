cmake_minimum_required(VERSION 3.28)
project(simcore)

# Setze die C++-Version
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Release)

# Compiler-Flags
# TODO:remove -ftrapv for release builds
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -Wconversion -Wdouble-promotion -Wcast-align -Wcast-qual -Wmissing-declarations -Wpointer-arith -Wreturn-type -Wno-unused-parameter -Wno-unused-function -Wno-sign-conversion -pedantic-errors -march=native -mtune=native -mfpmath=sse -msse4.1 -msse4.2 -flto -fno-math-errno -fno-signaling-nans -fno-trapping-math -freciprocal-math -Wdeprecated -fsanitize=undefined -ftrapv")

# Include-Verzeichnisse
include_directories(src)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

# Finde SDL2 und SDL2_image
FIND_PACKAGE( Boost 1.74 REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(CGAL REQUIRED)


# Quell-Dateien explizit angeben (ohne simcore.cpp which is main)
set(SOURCES
        src/appconfig.cpp
        src/worldmodel/Line.cpp
        src/location.cpp
        src/locations.cpp
        src/organism.cpp
        src/organism_manager.cpp
        src/worldmodel/Point.cpp
        src/worldmodel/Rectangle.cpp
        src/sensor.cpp
        src/sim_util.cpp
        src/visualize.cpp
        src/visualize_gui.cpp
        src/world.cpp
)

# Create a library from the source files
add_library(simcore_lib STATIC ${SOURCES})
target_link_libraries(simcore_lib PUBLIC SDL2::SDL2 SDL2_image::SDL2_image pthread CGAL::CGAL)

# Zieldefinition for executable
add_executable(simcore src/simcore.cpp)
target_link_libraries(simcore PRIVATE simcore_lib)

enable_testing()

add_executable(
        organism_test
        test/organismtest_test.cpp
)
target_link_libraries(
        organism_test
        GTest::gtest_main
        simcore_lib
)

include(GoogleTest)
gtest_discover_tests(organism_test)

# Add world_test target for World unit tests
add_executable(
    world_test
    test/world_test.cpp
)
# Define UNIT_TEST for the test compilation so FRIEND_TEST is active
target_compile_definitions(world_test PRIVATE UNIT_TEST)
# Link against gtest, CGAL, and simcore_lib
target_link_libraries(
    world_test
    GTest::gtest_main
    CGAL::CGAL
    simcore_lib
)
# Register with CTest
gtest_discover_tests(world_test)
