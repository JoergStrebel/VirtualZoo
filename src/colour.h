// SPDX-FileCopyrightText: 2023 Jörg Strebel <email>
// SPDX-License-Identifier: Apache-2.0

#ifndef COLOUR_H
#define COLOUR_H

#include <cstdint>
#include <string>

class Colour
{
private:            
    
public:
    Colour(uint8_t r, uint8_t g, uint8_t b, const std::string& name) : r(r), g(g), b(b), name(name) {}
    const uint8_t r;
    const uint8_t g;
    const uint8_t b;
    const std::string name;
};

#endif
