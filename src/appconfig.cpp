// SPDX-FileCopyrightText: 2023 <copyright holder> <email>
// SPDX-License-Identifier: Apache-2.0

#include "appconfig.h"

#include <map>
#include <string>

appconfig::appconfig()
{
    //some values are hardcoded here (later, we will load them dynamically from a file)
    //the keys are defined on application level
    this->put("beetle", "/home/jstrebel/devel/VirtualZoo/resource/beetle_square.png");
    this->put("bush", "/home/jstrebel/devel/VirtualZoo/resource/bush-clipart-xl.png");
}

appconfig::~appconfig()
{
}

std::string appconfig::get(std::string_view key) const {
    return imagepaths.at(std::string(key));
}

void appconfig::put(std::string_view key, std::string_view value){
    imagepaths[std::string(key)] = std::string(value);
}

std::vector<std::string> appconfig::get_keys() const {
    std::vector<std::string> keys;
    keys.reserve(this->imagepaths.size());
    for (auto const& [key, val] : imagepaths) {
        keys.push_back(key);
    }
    return keys;
}


