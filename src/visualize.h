// SPDX-FileCopyrightText: 2023 Jörg Strebel <email>
// SPDX-License-Identifier: Apache-2.0

#ifndef VISUALIZE_H
#define VISUALIZE_H
#include <string>
#include "appconfig.h"
#include "world.h"


/**
 * Virtual base class for any visualization logic
 */
class visualize
{
public:
    /**
     * Default constructor
     */
    visualize();
    
    //pure virtual function
    virtual bool init() = 0;
    
    //load media ressources
    virtual bool load_media(const appconfig& values) = 0;
    
    //draw the whole scene
    virtual void draw(const World& myWorld) = 0;

    //process exit events - exit happens when visualization is stopped
    virtual bool check_exit() = 0;

    /**
     * Destructor
     */
    virtual ~visualize();

private:

    
};

#endif // VISUALIZE_H

