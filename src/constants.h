#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "colour.h"
#include <string>

//  Purpose : Global Constants for Simulation
namespace Constants
{  
  
    enum Edibility_Constants {FOOD = 2, POISON = 3, NOTHING = 1};
    enum Vegetation_Constants {TREE = 1, PLANT=2, EMPTY = 3};
    constexpr int MAXYIELD=100;
    
    constexpr int MINX=0;
    constexpr int MINY=0;
    constexpr int MAXX=640;
    constexpr int MAXY=MAXX; //we'll have a square world
    constexpr int ENTITIESPERX = 20;
    constexpr int ENTITYSIZE = MAXX/ENTITIESPERX; //we assume square entites in the simulated world
    constexpr double PI = 3.141592;
    const Colour WHITE = Colour(255, 255, 255, "white");
    const Colour GREEN = Colour(69, 120, 8, "green");
    
}
#endif

