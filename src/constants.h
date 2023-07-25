#ifndef CONSTANTS_H
#define CONSTANTS_H

//  Purpose : Global Constants for Simulation
namespace Constants
{  
  
    enum Edibility_Constants {FOOD = 2, POISON = 3, NOTHING = 1};
    enum Vegetation_Constants {TREE = 1, PLANT=2, EMPTY = 3};
    const int MAXYIELD=100;
    
    const int MINX=0;
    const int MINY=0;
    const int MAXX=640;
    const int MAXY=MAXX; //we'll always have square worlds
    const int ENTITIESPERX = 20;
    const int ENTITYSIZE = MAXX/ENTITIESPERX; //we assume square entites in the simulated world
}
#endif

