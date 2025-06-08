// SPDX-FileCopyrightText: 2023 Jörg Strebel <email>
// SPDX-License-Identifier: Apache-2.0

#include "location.h"
#include "constants.h"
#include "sim_util.h"
#include "colour.h"
#include "Point.h"
#include "Line.h"
#include "Rectangle.h"

Location::Location(int px, int py, bool transp, int veg, std::string_view name, const Colour& col) :     
    top_left(px, py), 
    bottom_right(px+Constants::ENTITYSIZE, py+Constants::ENTITYSIZE), 
    name(std::string(name)),     
    area(Rectangle( 
        Line(Point(px,py),Point(px+Constants::ENTITYSIZE,py)), 
        Line(Point(px+Constants::ENTITYSIZE,py),Point(px+Constants::ENTITYSIZE,py+Constants::ENTITYSIZE)), 
        Line(Point(px+Constants::ENTITYSIZE,py+Constants::ENTITYSIZE),Point(px,py+Constants::ENTITYSIZE)), 
        Line(Point(px,py+Constants::ENTITYSIZE),Point(px,py)))),
    color(col)
    {
        maxyield  = rndnum.randomint(1, Constants::MAXYIELD);
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

const Point_2& Location::getTopLeft_new() const {
    return top_left_new;
}


