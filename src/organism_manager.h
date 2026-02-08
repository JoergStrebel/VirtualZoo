#ifndef ORGANISM__MANAGER_H
#define ORGANISM__MANAGER_H
#include "constants.h"
#include "sim_util.h"

class Organism;

/**
 * Manager class of each organism; it stores details needed for the simulation
 * This class mediates between the world and the organism
 */
class Organism_Manager
{
public:
    Organism_Manager();
    double x; //x-coordinate of location in the world 
    double y; //coordinate    
    void register_organism(Organism* org);
    void turn_around(int addx, int addy);
    void move(); //move one unit in the current heading
    void getFoV(double& leftBound, double& rightBound) const; //calculate the left and right bound of the field of view based on the current heading
    double get_heading() const;
    const double stepsize=2.0;
    static constexpr double field_of_view_rad = Constants::PI/2.0; //90° in rad

private:    
    Organism* organism;
    //heading is defined as any mathematician would define it:
    //units are rad, 0.0 is heading right, PI/2 is heading up, PI is heading left, 3/2PI is heading down
    double heading;
    double determine_opposite_direction(int addx, int addy) const;
    void turn(double radians);
    const sim_util util;
};

#endif // ORGANISM__MANAGER_H
