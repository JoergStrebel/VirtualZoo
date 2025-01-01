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
}

appconfig::~appconfig()
{
}

std::string appconfig::get(std::string key) const {
    return imagepaths.at(key);
}

void appconfig::put(std::string key, std::string value){
    imagepaths[key] = value;
}

std::vector<std::string> appconfig::getKeys() const {
    std::vector<std::string> keys;
    keys.reserve(this->imagepaths.size());
    for (auto const& [key, val] : imagepaths) {
        keys.push_back(key);
    }
    return keys;
}


