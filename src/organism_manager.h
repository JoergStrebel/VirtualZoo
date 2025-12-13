#ifndef ORGANISM__MANAGER_H
#define ORGANISM__MANAGER_H
#include "constants.h"

class Organism;

/**
 * Manager class of each organism; it stores details needed for the simulation
 * This class mediates between the world and the organism
 */
class Organism_Manager
{
public:
    Organism_Manager();
    // 0.0 is heading north, 90.0 is heading east, 180.0 is heading south, 270.0 is heading west
    // counting is clockwise
    double heading;
    double field_of_view_rad = Constants::PI/2.0; //90° in rad
    double x; //x-coordinate of location in the world 
    double y; //coordinate    
    void register_organism(Organism* org);
    void turn_around(int addx, int addy);
    void move(); //move one unit in the current heading

private:    
    Organism* organism;
    double stepsize=2.0;    
    double determine_opposite_direction(int addx, int addy) const;
    void turn(double degrees); //turn one unit based on the current heading
};

#endif // ORGANISM__MANAGER_H
