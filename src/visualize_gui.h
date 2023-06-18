// SPDX-FileCopyrightText: 2023 Jörg Strebel <email>
// SPDX-License-Identifier: Apache-2.0

#ifndef VISUALIZE_GUI_H
#define VISUALIZE_GUI_H
#include <SDL2/SDL.h>
#include <string>
#include "visualize.h"


/**
 * @todo write docs
 */
class visualize_gui : public visualize
{
public:
    /**
     * Default constructor
     */
    visualize_gui();
    
    //SDL2 setup
    bool init() override;
    
    //load media ressources
    bool load_media() override;
    
    //draw the scene
    bool draw() override;

    /**
     * Destructor
     */
    ~visualize_gui();

private:
    //The window we'll be rendering to
    SDL_Window* gWindow = NULL;
    
    //The surface contained by the window
    SDL_Surface* gScreenSurface = NULL;

    //SDL_Renderer* renderer;
    //Current displayed PNG image
    SDL_Surface* gPNGSurface = NULL;
    
    SDL_Surface* loadSurface( std::string path );
    
};

#endif // VISUALIZE_H
