// SPDX-FileCopyrightText: 2023 Jörg Strebel <email>
// SPDX-License-Identifier: Apache-2.0

#include "organism.h"
#include <iostream>
#include <algorithm>
#include "constants.h"
#include "sim_util.h"
#include "sensor.h"



Organism::Organism(const std::string id): identifier(id) {
 this->heading=0.0;
 this->x = 10;
 this->y = 10;
 //the following coordinates are entity coordinates in world pixels.
 sensorarray[0] = new sensor("pressure", "p1", 5, 2);
 sensorarray[1] = new sensor("pressure", "p2", 12, 1);
 sensorarray[2] = new sensor("pressure", "p3", 20, 1);
 sensorarray[3] = new sensor("pressure", "p3", 25, 2);
 sensorarray[4] = new sensor("pressure", "p3", 31, 21);
 sensorarray[5] = new sensor("pressure", "p3", 25, 31);
 sensorarray[6] = new sensor("pressure", "p3", 5, 31);
 sensorarray[7] = new sensor("pressure", "p3", 1, 21);

}

Organism::~Organism(){

}

void Organism::eat() {
    std::cout << "Eating...";
}

void Organism::act() {
    this->move();
}

void Organism::physical_stimulus(const std::string st){
    std::cout << "Received stimulus: " << st << std::endl;
    allstimuli.push_back(st);
}


void Organism::turn() {

}


void Organism::move() {
    //int movex = rndnums.randomint(-3,3);
    //int movey = rndnums.randomint(-3,3);

}
