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
    // 0.0 is heading north, 90.0 is heading east, 180.0 is heading south, 270.0 is heading west
    // counting is clockwise
    double heading;
    //TODO: why would the organism know his own the x/y coordinate? This is an implementation detail
    int x; //x-coordinate of location in the world 
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
    void turn(const double degrees); //turn one unit based on the current heading
    void move(); //move one unit in the current heading
    std::vector<std::string> allstimuli;
    
    //get direction of the stimulus in centered entity coordinates (0,0) is in the middle of the entity
    std::pair<int,int> getStimulusDirection(const std::string identifier);
    
    
};

#endif // ORGANISM_H
