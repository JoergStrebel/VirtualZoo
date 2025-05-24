// SPDX-FileCopyrightText: 2023 Jörg Strebel <email>
// SPDX-License-Identifier: Apache-2.0

#ifndef SENSOR_H
#define SENSOR_H

#include <string>

/**
 * Class SENSOR is an abstract class which represents all kinds of physical stimuli that an organism can receive.
 * For example: touch, sound, light ...
 * This class does not represent a specific information - it just receives the outside event.
 * In case of a collision, a pressure-sensitive sensor is triggered and send a message to the nervous system of the
 * organism. The stimulus itself (The semantic interpretation of the message) is interpreted by the organism's brain.
 * The message does not carry any information.
 * This class represents the stimuli of one sensor / one receptor in the organism body.
 */
class sensor
{
public:
    /**
     * Default constructor
     * the identifier is unique per organism, no matter what type of sensor is modeled
     */
    sensor(std::string_view typedesc, std::string_view identifier, const int x, const int y);
    
    const std::string get_type() const;
    const std::string get_id() const;
    const int x; //coordinate relative to the body of an organism
    const int y; //coordinate relative to the body of an organism
    /**
     * Destructor
     */
    virtual ~sensor();

private:
    const std::string typedesc;
    const std::string identifier;
};

#endif // SENSOR_H

