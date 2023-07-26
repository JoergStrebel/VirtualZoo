// SPDX-FileCopyrightText: 2023 Jörg Strebel <email>
// SPDX-License-Identifier: Apache-2.0

#ifndef STIMULUS_H
#define STIMULUS_H

#include <string>

/**
 * Class stimulus is an abstract class which represents all kinds of physical stimuli that an organism can receive.
 * For example: touch, sound, light ...
 * data is a pointer to a dynamically generated data object.
 */
class stimulus
{
public:
    /**
     * Default constructor
     */
    stimulus(const std::string& typedesc, const void* data);
    
    const void* get_data() const;
    const std::string get_id() const;
    
    /**
     * Destructor
     */
    virtual ~stimulus();

private:
    const std::string typedesc;
    const void* data = nullptr;

};

#endif // STIMULUS_H

