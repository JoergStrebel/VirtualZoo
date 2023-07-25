// SPDX-FileCopyrightText: 2023 Jörg Strebel <email>
// SPDX-License-Identifier: Apache-2.0

#include "organism.h"
#include <iostream>
#include <algorithm>
#include "constants.h"
#include "sim_util.h"

Organism::Organism(std::string id){
 this->identifier=id;
 this->heading=180.0;
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

void Organism::turn() {

}

void Organism::move() {
    int movex = rndnums.randomint(-3,3);
    int movey = rndnums.randomint(-3,3);

    this->y=std::min(this->y+movey, Constants::MAXY-Constants::ENTITYSIZE);
    this->x=std::min(this->x+movex, Constants::MAXX-Constants::ENTITYSIZE);
    this->y=std::max(this->y+movey, 0);
    this->x=std::max(this->x+movex, 0);
}
