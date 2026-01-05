#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "colour.h"
#include <string>
#include <climits>

//  Purpose : Global Constants for Simulation
namespace Constants
{  
  
    enum Edibility_Constants {FOOD = 2, POISON = 3, NOTHING = 1};
    enum Vegetation_Constants {TREE = 1, PLANT=2, EMPTY = 3};
    const int MAXYIELD=100;
    
    const int MINX=0;
    const int MINY=0;
    const int MAXX=640;
    const int MAXY=MAXX; //we'll have a square world
    const int ENTITIESPERX = 20;
    const int ENTITYSIZE = MAXX/ENTITIESPERX; //we assume square entites in the simulated world
    const double PI = 3.141592;
    const Colour WHITE = Colour(255, 255, 255, "white");
    const Colour GREEN = Colour(69, 120, 8, "green");
    const double UNLIMITEDSIGHTDISTANCE = -1.0; //use negative value for unlimited sight distance
    const int ANGULAR_RESOLUTION = 100;  // 1D screen resolution: 100 angular pixels

}
#endif

