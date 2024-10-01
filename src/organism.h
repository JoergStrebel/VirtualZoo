// SPDX-FileCopyrightText: 2023 Jörg Strebel <email>
// SPDX-License-Identifier: Apache-2.0

#ifndef ORGANISM_H
#define ORGANISM_H
#include <string>
#include "sim_util.h"
#include "sensor.h"
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
    void physical_stimulus(const std::string st);
    double heading;
    int x; //coordinate
    int y; //coordinate    
    //TODO: implement the rule of 3 or 5
    sensor* sensorarray[8];

private:
    const int MAXENERGY=100;
    const std::string identifier;

    int energy;
    float risklevel;
    double stepsize=2.0;

    void eat();
    void turn(const int degrees); //turn one unit based on the current heading
    void move(); //move one unit in the current heading
    sim_util rndnums;
    std::vector<std::string> allstimuli;
    
    //get direction of the stimulus in centered entity coordinates (0,0) is in the middle of the entity
    std::pair<int,int> getStimulusDirection(const std::string identifier);
    
    
};

#endif // ORGANISM_H
