#include "organism.h"
#include "organism_manager.h"
#include <iostream>
#include "constants.h"
#include <cmath>
#include <algorithm>

Organism_Manager::Organism_Manager(){ 
    this->heading=0.0;
    this->x = 400.0;
    this->y = 400.0;
}

void Organism_Manager::move() {
    //transform into standard radian angle
    double radAngle = (heading/360.0)*2*Constants::PI;
    double deltay = stepsize*std::cos(radAngle);
    y=y-deltay; //y-axis is inverted
    double deltax = stepsize*std::sin(radAngle);
    x=x+deltax;
    std::cout << "Step: " << deltax << ", " << deltay << std::endl;
}


// turn the organism by a certain amount of degrees
void Organism_Manager::turn(const double degrees) {
    heading += degrees;
    heading = heading - 360.0*std::floor(heading/360.0);
    std::cout << "New heading: " << heading << std::endl;    
}

void Organism_Manager::turn_around(int addx, int addy){
    double headingdiff = determine_opposite_direction(addx, addy);
    this->turn(headingdiff);
}

void Organism_Manager::register_organism(Organism* org){
    //register the organism
    organism=org;
}

double Organism_Manager::determine_opposite_direction(int addx, int addy) {
      //determine the direction from which the stimuli come          
        //derive direction from the stimdir
        //turn around in the opposite direction of the stimuli        
        // arctan2 liefert -pi ... pi 
        //see https://en.cppreference.com/w/cpp/numeric/math/atan2
        // we need -addy because the y-axis is inverted
        double radAngle = std::atan2((double)-addy, (double)addx); // -pi ... pi radians
        double targetAngle = 180.0*(radAngle/(Constants::PI)); // -180 ... 180 degrees
        std::cout << "target angle of stimulus: " << targetAngle << std::endl;
        //targetAngle =0 --> stimuliAngle = 90
        //targetAngle =90 --> stimuliAngle = 0
        //targetAngle =180 --> stimuliAngle = 270
        //targetAngle = -90 --> stimuliAngle = 180
        //targetAngle = -180 --> stimuliAngle = 270
        double calcHeading = 360.0-(targetAngle-90.0); // calculate to 360 degrees pointing upwards 
        std::cout << "calculated heading of stimulus: " << calcHeading << std::endl;
        // normalize calcHeading to 0...360
        double normCalcHeading = calcHeading - 360.0*std::floor(calcHeading/360.0);
        std::cout << "Normalized heading of stimulus: " << normCalcHeading << std::endl;
        //calculate the opposite heading as the new direction
        double OppHeading = normCalcHeading + 180.0;
        std::cout << "Opposing heading of stimulus: " << OppHeading << std::endl;
        double normOppHeading = OppHeading - 360.0*std::floor(OppHeading/360.0);
        std::cout << "Normalized opposing heading of stimulus: " << normOppHeading << std::endl;
        double headingdiff = normOppHeading-heading;
        std::cout << "Degrees to turn: " << headingdiff << std::endl;
        return headingdiff;
}
