// SPDX-FileCopyrightText: 2023 Jörg Strebel <email>
// SPDX-License-Identifier: Apache-2.0

#include "world.h"


World::World()
{
    myOrg = new Organism("beetle");
}

void World::run_world(){
   myOrg->act();
}

