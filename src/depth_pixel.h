// SPDX-FileCopyrightText: 2023 Jörg Strebel <email>
// SPDX-License-Identifier: Apache-2.0

#ifndef DEPTH_PIXEL_H
#define DEPTH_PIXEL_H

#include <optional>
#include "colour.h"

struct DepthPixel {
    double depth;                        // squared distance from ray intersection
    std::optional<int> location_index;   // nullopt if no object visible
    double angle;                        // ray angle in radians [0, 2π)
    std::optional<Colour> world_color;   // nullopt if no object visible
};

#endif // DEPTH_PIXEL_H
