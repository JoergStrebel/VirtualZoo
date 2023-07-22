// SPDX-FileCopyrightText: 2023 <copyright holder> <email>
// SPDX-License-Identifier: Apache-2.0

#ifndef APPCONFIG_H
#define APPCONFIG_H

#include <string>
#include <map>


/**
 * @todo write docs
 */
class appconfig
{
public:
    appconfig();
    ~appconfig();

    std::string get(std::string key);
    void put(std::string key, std::string value);

private:
    std::map<std::string, std::string> imagepaths;

};

#endif // APP-CONFIG_H
