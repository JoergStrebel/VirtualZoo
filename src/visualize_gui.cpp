// SPDX-FileCopyrightText: 2023 Jörg Strebel <email>
// SPDX-License-Identifier: Apache-2.0

#include "visualize_gui.h"
#include <SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include <iostream>
#include <string>


//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
    
visualize_gui::visualize_gui()
{
                
}

visualize_gui::~visualize_gui()
{
    SDL_Log( "GUI Destructor called");
   //Free loaded image
	SDL_FreeSurface( gPNGSurface );
	gPNGSurface = NULL;

	//Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();

}

bool visualize_gui::init()
{
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        SDL_Log("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    } else
    {
          //Create window
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            SDL_Log( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            return false;
        }
        else
        {
            //Get window surface
            gScreenSurface = SDL_GetWindowSurface( gWindow );
        }
        //renderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_PRESENTVSYNC);
    }
    
    return true;
}

bool visualize_gui::load_media()
{    
    std::string path = "/home/jstrebel/devel/VirtualZoo/resource/loaded.png"; 
    bool success = true;
    
    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        SDL_Log( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        success = false;
    }
    
	//Load PNG surface
	gPNGSurface = loadSurface( path );
	if( gPNGSurface == NULL )
	{
		SDL_Log( "Failed to load PNG image!\n" );
		success = false;
	}

	return success;
}


SDL_Surface* visualize_gui::loadSurface( std::string path )
{
	//The final optimized image
	SDL_Surface* optimizedSurface = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		SDL_Log( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, 0 );
		if( optimizedSurface == NULL )
		{
			SDL_Log( "Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return optimizedSurface;
}


bool visualize_gui::draw()
{
    SDL_Event e; 
    bool quit = false; 
    SDL_BlitSurface( gPNGSurface, NULL, gScreenSurface, NULL );
    //Update the surface
    SDL_UpdateWindowSurface( gWindow );
    
    while( quit == false )
    { 
        while( SDL_PollEvent( &e ) )
        { 
            if( e.type == SDL_QUIT ) quit = true; 
            
        }         
        //TODO: if there is not SDL_PollEvent, nothing gets drawn?? Why?
        //A: it seems, we need to call both commands continuously for them to work
        SDL_BlitSurface( gPNGSurface, NULL, gScreenSurface, NULL );
        //Update the surface
        SDL_UpdateWindowSurface( gWindow );
    }
    return true;
}
