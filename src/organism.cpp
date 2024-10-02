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
   /* 
    //check for received stimuli
    if (allstimuli.size()>0) {
        for (std::string stimulus : allstimuli)
        {
            stimdir = this->getStimulusDirection(stimulus);
            //TODO: determine the direction from which the stimuli come
            //TODO: derive direction from the stimdir
        }
        // if yes, react to stimuli
        // TODO: turn around in the opposite direction of the stimuli
        //this->turn(...);        
    }
    else {*/
        //if no, make your next move.
        int degrees = rndnums.randomint(-1,1);
        this->turn(degrees);
        this->move();
    //}
}

void Organism::physical_stimulus(const std::string st){
    std::cout << "Received stimulus: " << st << std::endl;
    allstimuli.push_back(st);
}


void Organism::turn(const int degrees) {
    heading += degrees;
    if (heading<0) heading=heading+360.0;    
    if (heading>360.0) heading=heading-360.0;
}


void Organism::move() {        
    y=y+stepsize*std::sin(heading+90.0);
    x=x+stepsize*std::cos(heading+90.0);
}

std::pair<int,int> Organism::getStimulusDirection(const std::string identifier){
     for(int i=0;i<=7;i++){
        sensor* currentsens = this->sensorarray[i];
        if (currentsens->get_id()==identifier) return std::make_pair(currentsens->x, currentsens->y);
    }
    return std::make_pair(0, 0);
}


