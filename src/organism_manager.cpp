#include "organism.h"
#include "organism_manager.h"
#include <iostream>
#include "constants.h"
#include <cmath>
#include <algorithm>
#include "sim_util.h"

Organism_Manager::Organism_Manager(){ 
    this->heading=Constants::PI;
    this->x = 400.0;
    this->y = 400.0;
    organism=nullptr; //to be set when the organism registers itself
}

void Organism_Manager::move() {
    //transform into standard radian angle
    double deltay = stepsize*std::cos(heading);
    y=y-deltay; //y-axis is inverted
    double deltax = stepsize*std::sin(heading);
    x=x+deltax;
    //std::cout << "Step: " << deltax << ", " << deltay << std::endl;
}

// turn the organism by a certain number of degrees
void Organism_Manager::turn(const double radians) {
     //normalize to 0 ... 2pi radians
    heading = util.normalize(heading+radians);
}

void Organism_Manager::turn_around(int addx, int addy){
    double headingdiff = determine_opposite_direction(addx, addy);
    this->turn(headingdiff);
}

void Organism_Manager::register_organism(Organism* org){
    //register the organism
    organism=org;
}

//Returns the angle in rad that the organism needs to turn to face away from the stimulus
double Organism_Manager::determine_opposite_direction(int addx, int addy) const {
      //determine the direction from which the stimuli come          
        //derive direction from the stimdir
        //turn around in the opposite direction of the stimuli        
        // arctan2 liefert -pi ... pi 
        //see https://en.cppreference.com/w/cpp/numeric/math/atan2
        // we need -addy because the y-axis is inverted
        double radAngle = std::atan2((double)-addy, (double)addx); // -pi ... pi radians
        double OppHeading = radAngle + Constants::PI; // add pi to get the opposite direction, still in -pi ... pi
        double normOppHeading = util.normalize(OppHeading); // normalize to 0 ... 2pi radians
        return normOppHeading-heading;
}

void Organism_Manager::getFoV(double& leftBound, double& rightBound) const {
    // Calculate left and right bounds of the field of view based on current heading
    double halfFoV = field_of_view_rad / 2.0;

    leftBound = util.normalize(heading - halfFoV);
    rightBound = util.normalize(heading + halfFoV);
}

double Organism_Manager::get_heading() const {
    return heading;
}