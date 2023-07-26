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
    std::cout << "Received stimulus %s" << st;
    allstimuli.push_back(st);
}


void Organism::turn() {

}

void Organism::move() {
    int movex = rndnums.randomint(-3,3);
    int movey = rndnums.randomint(-3,3);

}
