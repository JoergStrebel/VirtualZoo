// SPDX-FileCopyrightText: 2023 Jörg Strebel <email>
// SPDX-License-Identifier: Apache-2.0

#include "organism.h"
#include <iostream>
#include <algorithm>
#include "constants.h"

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
    this->y=std::min(this->y+1, Constants::MAXY);
}
