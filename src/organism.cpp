// SPDX-FileCopyrightText: 2023 Jörg Strebel <email>
// SPDX-License-Identifier: Apache-2.0

#include "organism.h"
#include <iostream>
#include "constants.h"
#include "sensor.h"
#include "organism_manager.h"


Organism::Organism(const std::string_view id, Organism_Manager& manager): identifier(std::string(id)), om(manager) {
    this->energy = MAXENERGY;
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

Organism::~Organism()= default;

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
        for (const std::string& stimulus : allstimuli)
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

void Organism::physical_stimulus(const std::string_view st){
    std::cout << "Received stimulus: " << st << std::endl;
    allstimuli.emplace_back(st);
}

std::pair<int,int> Organism::getStimulusDirection(const std::string_view id_object){
     for(int i=0;i<=7;i++){
        sensor* currentsens = this->sensorarray[i];
        if (currentsens->get_id()==id_object) return std::make_pair(currentsens->x, currentsens->y);
    }
    return std::make_pair(0, 0);
}

void Organism::step_forward(){
    om.move();
}

void Organism::move_towards(const double visual_direction){}

bool Organism::detect_collision(){
    return !allstimuli.empty();
}

void Organism::recognize(){}

// receiver mehod for the visual stimulus, which is an array of depth pixels, each containing
// the distance to the nearest object in that direction and
// the color of that object
// the array is already trimmed to the field of view of the organism, so it only contains the pixels that are visible to the organism
void Organism::visual_stimulus(const std::vector<Colour>& world_color, const std::vector<double>& world_distance){
    std::cout << "Received visual stimulus: " << std::endl;
    //erase previous retina content
    retina_color.fill(0);
    retina_distance.fill(Constants::UNLIMITEDSIGHTDISTANCE);

    // TODO: translate the depth buffer onto pixels on the retina - depth mapping, pixel rendering
    // std::array<int, RETINA_RES> retina_color;
    // std::array<double, RETINA_RES> retina_distance;

}

