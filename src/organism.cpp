// SPDX-FileCopyrightText: 2023 Jörg Strebel <email>
// SPDX-License-Identifier: Apache-2.0

#include "organism.h"
#include <iostream>
#include "organism_manager.h"


// sensor coordinates are entity-local in world pixels; (0,0) is the entity center.
// real world address = myOrgMan.x + ENTITYSIZE/2 + sensor.x
Organism::Organism(const std::string_view id, Organism_Manager& manager)
    : sensorarray{{
          sensor("pressure", "p0",  5 + shiftcenter,  2 + shiftcenter),
          sensor("pressure", "p1", 12 + shiftcenter,  1 + shiftcenter),
          sensor("pressure", "p2", 20 + shiftcenter,  1 + shiftcenter),
          sensor("pressure", "p3", 25 + shiftcenter,  2 + shiftcenter),
          sensor("pressure", "p4", 31 + shiftcenter, 21 + shiftcenter),
          sensor("pressure", "p5", 25 + shiftcenter, 31 + shiftcenter),
          sensor("pressure", "p6",  5 + shiftcenter, 31 + shiftcenter),
          sensor("pressure", "p7",  1 + shiftcenter, 21 + shiftcenter)
      }},
      identifier(std::string(id)),
      energy(MAXENERGY),
      om(manager)
{
    om.register_organism(this);
}

Organism::~Organism()= default;

void Organism::eat() {
    std::cout << "Eating...";
}

void Organism::act() {
    //check for received stimuli
    if (detect_collision()) {
        int addy=0;
        int addx=0;
        std::pair<int, int> stimdir;
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
    allstimuli.clear();
}

void Organism::physical_stimulus(const std::string_view st){
    std::cout << "Received stimulus: " << st << std::endl;
    allstimuli.emplace_back(st);
}

std::pair<int,int> Organism::getStimulusDirection(const std::string_view id_object) const {
     for(std::size_t i = 0; i < std::size(sensorarray); ++i){
        const sensor& currentsens = this->sensorarray[i];
        if (currentsens.get_id()==id_object) return std::make_pair(currentsens.x, currentsens.y);
    }
    return std::make_pair(0, 0);
}

void Organism::step_forward(){
    om.move();
}

void Organism::move_towards(const double visual_direction){}

bool Organism::detect_collision() const {
    return !allstimuli.empty();
}

void Organism::recognize(){}

// receiver method for the visual stimulus, which is an array of depth pixels, each containing
// the distance to the nearest object in that direction, the color of that object and the angle
// the array is already trimmed to the field of view of the organism, so it only contains the pixels that are visible to the organism
void Organism::visual_stimulus(const std::vector<DepthPixel>& depth_buffer){
    std::cout << "Received visual stimulus: " << std::endl;
    //erase previous retina content
    retina_color.fill(0);
    retina_distance.fill(Constants::UNLIMITEDSIGHTDISTANCE);

    // TODO: translate the depth buffer onto pixels on the retina - depth mapping, pixel rendering
}

