// SPDX-FileCopyrightText: 2023 Jörg Strebel <email>
// SPDX-License-Identifier: Apache-2.0

#ifndef ORGANISM_H
#define ORGANISM_H
#include <string>

/**
 * @todo write docs
 */
class Organism
{
public:
    Organism(std::string id);
    ~Organism();
    void act();
    float heading;
    int x; //coordinate
    int y; //coordinate

private:
    const int MAXENERGY=100;

    int energy;
    float risklevel;
    std::string identifier;
    
    void eat();
    void turn(); //turn one unit based on the current heading
    void move(); //move one unit in the current heading
    
};

#endif // ORGANISM_H
