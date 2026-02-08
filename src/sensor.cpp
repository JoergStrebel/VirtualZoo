// SPDX-FileCopyrightText: 2023 Jörg Strebel <email>
// SPDX-License-Identifier: Apache-2.0

#include "sensor.h"
#include <string>

/**
 * @todo write docs
 */

sensor::sensor(std::string_view typedesc, std::string_view identifier, const int x, const int y):
x(x), y(y), typedesc(std::string(typedesc)), identifier(std::string(identifier))
    {
    }

sensor::~sensor()
{
}


std::string sensor::get_id() const {
    return identifier;
}

std::string sensor::get_type() const {
    return typedesc;
}

