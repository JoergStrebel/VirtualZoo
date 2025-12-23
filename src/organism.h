// SPDX-FileCopyrightText: 2023 Jörg Strebel <email>
// SPDX-License-Identifier: Apache-2.0

#ifndef ORGANISM_H
#define ORGANISM_H
#include <string>
#include <array>
#include "sim_util.h"
#include "Projection.h"
#include "sensor.h"
#include <vector>
#include <array>

class Organism_Manager;

/**
 * @todo write docs
 */
class Organism
{
public:
    Organism(std::string_view id, Organism_Manager& manager);
    ~Organism();
    void act();
    void physical_stimulus(std::string_view st);
    sensor* sensorarray[8]{};
    void visual_stimulus(const std::vector<Projection>& projections);

private:
    static constexpr int MAXENERGY=100;    
    const std::string identifier;
    int energy;
    static constexpr int RETINA_RES=90;
    std::array<int, RETINA_RES> retina_color{};
    std::array<double, RETINA_RES> retina_distance{};

    Organism_Manager& om;

    void eat();
    
    //check the retina for interesting things
    void recognize();    
    void move_towards(double visual_direction);
    void step_forward();
    bool detect_collision();
        
    std::vector<std::string> allstimuli;    
    
    //get the direction of the stimulus in centered entity coordinates (0,0) is in the middle of the entity
    std::pair<int,int> getStimulusDirection(std::string_view id_object);
};

#endif // ORGANISM_H
