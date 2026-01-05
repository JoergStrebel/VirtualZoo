// SPDX-FileCopyrightText: 2023 Jörg Strebel <email>
// SPDX-License-Identifier: Apache-2.0

#include "location.h"

#include <utility>
#include "constants.h"
#include "sim_util.h"
#include "colour.h"
#include "worldmodel/Point.h"
#include "worldmodel/Line.h"
#include "worldmodel/Rectangle.h"

Location::Location(int px, int py, bool transp, int veg, std::string_view name, Colour  col) :
    top_left(px, py),
    bottom_right(px + Constants::ENTITYSIZE, py + Constants::ENTITYSIZE),
    name(std::string(name)),
    area(Rectangle(
        Line(Point(px, py), Point(px + Constants::ENTITYSIZE, py)), //top
        Line(Point(px + Constants::ENTITYSIZE, py),
            Point(px + Constants::ENTITYSIZE, py + Constants::ENTITYSIZE)), //right
        Line(Point(px + Constants::ENTITYSIZE, py + Constants::ENTITYSIZE),
            Point(px, py + Constants::ENTITYSIZE)), //bottom
        Line(Point(px, py + Constants::ENTITYSIZE), Point(px, py)))), //left
    color(std::move(col)), top_left_new(px, py)
{
    maxyield = rndnum.randomint(1, Constants::MAXYIELD);
    availableyield = maxyield;
    vegetation = veg;
    transparency = transp;
}


const std::string Location::toString()
{
    return "Maxyield: "+std::to_string(maxyield);
}

const std::string Location::getName()
{
    return name;
}

const Point Location::getTopLeft()
{
    return top_left;
}
const Point& Location::getBottomRight() const
{
    return bottom_right;
}
const Rectangle& Location::getArea()
{
    return area;
}

const Point& Location::getTopLeft_new() const {
    return top_left_new;
}
const Colour& Location::getColor() const {
    return color;
}


