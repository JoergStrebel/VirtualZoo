cmake_minimum_required(VERSION 3.28)
project(simcore)

# Setze die C++-Version
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(CGAL REQUIRED)

# Quell-Dateien explizit angeben
set(SOURCES
        src/simcore.cpp
        src/appconfig.cpp
        src/Line.cpp
        src/location.cpp
        src/locations.cpp
        src/organism.cpp
        src/organism_manager.cpp
        src/Point.cpp
        src/Projection.cpp
        src/Rectangle.cpp
        src/sensor.cpp
        src/sim_util.cpp
        src/visualize.cpp
        src/visualize_gui.cpp
        src/world.cpp
)

# Zieldefinition
add_executable(simcore ${SOURCES})
# Linker-Optionen
target_link_libraries(simcore PRIVATE SDL2::SDL2 SDL2_image::SDL2_image pthread CGAL::CGAL)

enable_testing()

add_executable(
        organism_test
        test/organismtest_test.cpp
)
target_link_libraries(
        organism_test
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(organism_test)



