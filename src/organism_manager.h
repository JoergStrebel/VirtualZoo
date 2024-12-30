#ifndef ORGANISM__MANAGER_H
#define ORGANISM__MANAGER_H
#include "organism.h"

/**
 * Manager class of each indidivual organism; it stores details needed for the simulation
 */
class Organism_Manager
{
public:
    Organism_Manager(const Organism& organism);
    ~Organism_Manager();    
    // 0.0 is heading north, 90.0 is heading east, 180.0 is heading south, 270.0 is heading west
    // counting is clockwise
    double heading;    
    double x; //x-coordinate of location in the world 
    double y; //coordinate    
    //TODO: implement the rule of 3 or 5    

private:    
    const Organism& organism;
    double stepsize=2.0;
    void turn(const double degrees); //turn one unit based on the current heading
    void move(); //move one unit in the current heading
};

#endif // ORGANISM_MANAGER_H
