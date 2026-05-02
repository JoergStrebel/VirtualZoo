// SPDX-FileCopyrightText: 2023 Jörg Strebel <email>
// SPDX-License-Identifier: Apache-2.0

#ifndef ORGANISM_H
#define ORGANISM_H
#include <string>
#include <array>
#include "sensor.h"
#include <vector>
#include "depth_pixel.h"
#include "constants.h"

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
    std::array<sensor, 8> sensorarray;
    void visual_stimulus(const std::vector<DepthPixel>& depth_buffer);

private:
    static constexpr int MAXENERGY=100;
    static constexpr int shiftcenter = -Constants::ENTITYSIZE / 2;
    const std::string identifier;
    int energy;
    static constexpr int RETINA_RES=90; //retina resolution
    std::array<int, RETINA_RES> retina_color{};
    std::array<double, RETINA_RES> retina_distance{};

    Organism_Manager& om;

    void eat();
    
    //check the retina for interesting things
    void recognize();    
    void move_towards(double visual_direction);
    void step_forward();
    bool detect_collision() const;
        
    std::vector<std::string> allstimuli;    
    
    //get the direction of the stimulus in centered entity coordinates (0,0) is in the middle of the entity
    std::pair<int,int> getStimulusDirection(std::string_view id_object) const;
};

#endif // ORGANISM_H
