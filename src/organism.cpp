// SPDX-FileCopyrightText: 2023 Jörg Strebel <email>
// SPDX-License-Identifier: Apache-2.0

#include "organism.h"
#include <iostream>
#include <algorithm>
#include "constants.h"
#include "sim_util.h"
#include "sensor.h"
#include <cmath>


Organism::Organism(const std::string id): identifier(id) {
 this->heading=0.0;
 this->x = 400;
 this->y = 400;
 
 //the following coordinates are entity coordinates in world pixels 
 //(0,0) denotes the center of the entity.
 // the real, absolute pixel address is then x+shiftcenter+sensor.x
 //TODO: fix the addressing and fix the collision detection
 int shiftcenter = -1*Constants::ENTITYSIZE/2; //-32
 sensorarray[0] = new sensor("pressure", "p0", 5+shiftcenter, 2+shiftcenter);
 sensorarray[1] = new sensor("pressure", "p1", 12+shiftcenter, 1+shiftcenter);
 sensorarray[2] = new sensor("pressure", "p2", 20+shiftcenter, 1+shiftcenter);
 sensorarray[3] = new sensor("pressure", "p3", 25+shiftcenter, 2+shiftcenter);
 sensorarray[4] = new sensor("pressure", "p4", 31+shiftcenter, 21+shiftcenter);
 sensorarray[5] = new sensor("pressure", "p5", 25+shiftcenter, 31+shiftcenter);
 sensorarray[6] = new sensor("pressure", "p6", 5+shiftcenter, 31+shiftcenter);
 sensorarray[7] = new sensor("pressure", "p7", 1+shiftcenter, 21+shiftcenter);

}

Organism::~Organism(){

}

void Organism::eat() {
    std::cout << "Eating...";
}

void Organism::act() {
    
    std::pair<int, int> stimdir;
    int addx=0;
    int addy=0;
    
    //check for received stimuli
    if (allstimuli.size()>0) {
        for (std::string stimulus : allstimuli)
        {            
            stimdir = this->getStimulusDirection(stimulus);
            //add vectors to determine the direction of the stimuli, if there is more than one stimulus
            addx+=stimdir.first;
            addy+=stimdir.second;
        }        
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
        this->turn(headingdiff);
        this->move();
    } else //just move along the old course
    {
        this->move();
    }
}

void Organism::physical_stimulus(const std::string st){
    std::cout << "Received stimulus: " << st << std::endl;
    allstimuli.push_back(st);
}

// turn the organism by a certain amount of degrees
void Organism::turn(const double degrees) {
    heading += degrees;
    heading = heading - 360.0*std::floor(heading/360.0);
    std::cout << "New heading: " << heading << std::endl;    
}


void Organism::move() {
    //transform into standard radian angle
    double radAngle = (heading/360.0)*2*Constants::PI;
    int deltay = std::lround(stepsize*std::cos(radAngle));
    y=y-deltay; //y-axis is inverted
    int deltax = std::lround(stepsize*std::sin(radAngle));
    x=x+deltax;
    std::cout << "Step: " << deltax << ", " << deltay << std::endl;
}

std::pair<int,int> Organism::getStimulusDirection(const std::string identifier){
     for(int i=0;i<=7;i++){
        sensor* currentsens = this->sensorarray[i];
        if (currentsens->get_id()==identifier) return std::make_pair(currentsens->x, currentsens->y);
    }
    return std::make_pair(0, 0);
}


