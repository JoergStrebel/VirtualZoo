// SPDX-FileCopyrightText: 2023 Jörg Strebel <email>
// SPDX-License-Identifier: Apache-2.0

#include "sensor.h"
#include <string>

/**
 * @todo write docs
 */

sensor::sensor(const std::string typedesc, const std::string identifier, const int x, const int y):
x(x), y(y), typedesc(typedesc), identifier(identifier)
    {
    }

sensor::~sensor()
{
}


const std::string sensor::get_id() const {
    return identifier;
}

const std::string sensor::get_type() const {
    return typedesc;
}

