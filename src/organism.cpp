// SPDX-FileCopyrightText: 2023 Jörg Strebel <email>
// SPDX-License-Identifier: Apache-2.0

#include "organism.h"
#include <iostream>
#include "constants.h"
#include "sim_util.h"
#include "sensor.h"
#include "organism_manager.h"


Organism::Organism(const std::string id, Organism_Manager& manager): identifier(id), om(manager) {
    this->energy = MAXENERGY;
    this->risklevel = 0.0;  
    om.register_organism(this);

    //initialize the sensors
 
 //the following coordinates are entity coordinates in world pixels 
 //(0,0) denotes the center of the entity.
 // the real, absolute pixel address is then x+shiftcenter+sensor.x
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
    if (detect_collision()) {
    //Primitive behaviour: if you collide, turn around.

    //let the Organism_Manager do the calculations
        for (std::string stimulus : allstimuli)
        {            
            stimdir = this->getStimulusDirection(stimulus);
            //add vectors to determine the direction of the stimuli, if there is more than one stimulus
            addx+=stimdir.first;
            addy+=stimdir.second;
        } 
        om.turn_around(addx, addy);           
        this->step_forward();
    } else //just move along the old course
    {
        this->step_forward();
    }
}

void Organism::physical_stimulus(const std::string st){
    std::cout << "Received stimulus: " << st << std::endl;
    allstimuli.push_back(st);
}

std::pair<int,int> Organism::getStimulusDirection(const std::string identifier){
     for(int i=0;i<=7;i++){
        sensor* currentsens = this->sensorarray[i];
        if (currentsens->get_id()==identifier) return std::make_pair(currentsens->x, currentsens->y);
    }
    return std::make_pair(0, 0);
}

void Organism::step_forward(){
    om.move();
}

void Organism::move_towards(double visual_direction){}

bool Organism::detect_collision(){
    return allstimuli.size()>0;
}

void Organism::recognize(){} 

