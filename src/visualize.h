// SPDX-FileCopyrightText: 2023 Jörg Strebel <email>
// SPDX-License-Identifier: Apache-2.0

#ifndef VISUALIZE_H
#define VISUALIZE_H
#include <string>


/**
 * @todo write docs
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
    virtual bool load_media() = 0;
    
    //draw the whole scene
    virtual bool draw() = 0;

    /**
     * Destructor
     */
    virtual ~visualize();

private:
    
};

#endif // VISUALIZE_H

