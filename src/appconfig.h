// SPDX-FileCopyrightText: 2023 <copyright holder> <email>
// SPDX-License-Identifier: Apache-2.0

#ifndef APPCONFIG_H
#define APPCONFIG_H

#include <string>
#include <map>


/**
 * Defines the resouces used by the simulation, e.g. images for the visualization.
 */
class appconfig
{
public:
    appconfig();
    ~appconfig();

    std::string get(std::string key) const;
    void put(std::string key, std::string value);

private:
    std::map<std::string, std::string> imagepaths;

};

#endif // APP-CONFIG_H
