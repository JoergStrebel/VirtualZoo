// SPDX-FileCopyrightText: 2023 Jörg Strebel <email>
// SPDX-License-Identifier: Apache-2.0

#ifndef ORGANISM_H
#define ORGANISM_H
#include <string>
#include "sim_util.h"
#include "stimulus.h"
#include <vector>

/**
 * @todo write docs
 */
class Organism
{
public:
    Organism(const std::string id);
    ~Organism();
    void act();
    void physical_stimulus(const stimulus* st);
    float heading;
    int x; //coordinate
    int y; //coordinate

private:
    const int MAXENERGY=100;
    const std::string identifier;

    int energy;
    float risklevel;

    void eat();
    void turn(); //turn one unit based on the current heading
    void move(); //move one unit in the current heading
    sim_util rndnums;
    std::vector<const stimulus*> allstimuli;
    
};

#endif // ORGANISM_H
