// SPDX-FileCopyrightText: 2023 Jörg Strebel <email>
// SPDX-License-Identifier: Apache-2.0

#ifndef COLOUR_H
#define COLOUR_H

#include <cstdint>
#include <string>
#include <utility> // for std::move

class Colour
{
private:            
    
public:
    // take name by value and move into the member to avoid an extra copy
    Colour(uint8_t r, uint8_t g, uint8_t b, std::string name) : r(r), g(g), b(b), name(std::move(name)) {}
    const uint8_t r;
    const uint8_t g;
    const uint8_t b;
    const std::string name;
};

#endif
