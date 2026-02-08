// SPDX-FileCopyrightText: 2023 <copyright holder> <email>
// SPDX-License-Identifier: Apache-2.0

#include "sim_util.h"
#include <random>
#include "constants.h"

sim_util::sim_util() : e1(r())
{

}

int sim_util::randomint(const int minval, const int maxval){
        std::uniform_int_distribution<int> uniform_dist(minval, maxval);
        return uniform_dist(e1);
}

double sim_util::normalize(double radvalue) const {
        while (radvalue < 0) radvalue += 2.0 * Constants::PI;
        while (radvalue >= 2.0 * Constants::PI) radvalue -= ((double)2.0) * Constants::PI;
        return radvalue;
}
