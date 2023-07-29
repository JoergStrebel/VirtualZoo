// SPDX-FileCopyrightText: 2023 <copyright holder> <email>
// SPDX-License-Identifier: Apache-2.0

#ifndef SIM_UTIL_H
#define SIM_UTIL_H
#include <random>

/**
 * @todo write docs
 */
class sim_util
{
public:
    /**
     * Default constructor
     */
    sim_util();

    int randomint(const int minval, const int maxval);

    /**
     * Destructor
     */
    ~sim_util();

private:
    std::random_device r;
    std::default_random_engine e1;

};

#endif // SIM_UTIL_H
