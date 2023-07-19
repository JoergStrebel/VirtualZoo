// SPDX-FileCopyrightText: 2023 Jörg Strebel <email>
// SPDX-License-Identifier: Apache-2.0

#include "visualize_gui.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>


    
visualize_gui::visualize_gui()
{
                
}

visualize_gui::~visualize_gui()
{
   //Free loaded image

	//Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
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
    
	//Load PNG texture
	SDL_Texture*  gPNGSurface = loadTexture( path );
	if( gPNGSurface == NULL )
	{
		SDL_Log( "Failed to load PNG image!\n" );
		success = false;
	}

	return success;
}


SDL_Texture* visualize_gui::loadTexture( std::string path )
{

	//Load image at specified path
	SDL_Texture* loadedTexture = IMG_LoadTexture(renderer,  path.c_str() );
	if( loadedTexture == NULL )
	{
		SDL_Log( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}

	return loadedTexture;
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


bool visualize_gui::init()
{
	Uint32 flags;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        	fprintf(stderr, "Couldn't init video: %s\n", SDL_GetError());
        	exit(1);
    	}

	atexit(SDL_Quit);

    flags = SDL_WINDOW_SHOWN;
    gWindow = SDL_CreateWindow(windowtitle.c_str(), SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, flags);

    if (!gWindow) {
        	fprintf(stderr, "Couldn't set %dx%d video mode: %s\n",
                	SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
		exit(1);
	}

	// We must call SDL_CreateRenderer in order for draw calls to affect this window.
	renderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer) {
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Accelerated Renderer not available");
		renderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_SOFTWARE);
    }

	if (!renderer) {
		fprintf(stderr, "Couldn't find a renderer\n");
        exit(1);
	}

	SDL_ShowCursor(SDL_DISABLE);
    return true;
}

/* Draw a point. Surface must be locked with SDL_LockSurface(). */
void visualize_gui::drawpoint(unsigned int x, unsigned int y, struct color color)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawPoint(renderer, x, y);
}

void visualize_gui::clearscreen(void)
{
    struct color color;
    Uint8 a;

    SDL_GetRenderDrawColor(renderer, &color.r, &color.g, &color.b, &a);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, a);
}

void visualize_gui::updatedisplay(void)
{
	SDL_RenderPresent(renderer);
}

/**
 * It is assumed that the frames are stacked, i.e. the different frames can be addressed using the height parameter
 */
void visualize_gui::drawimage(int x, int y, int frame, struct W_Image *image)
{
	int height, width;
	SDL_Rect srcrect, dstrect;

	if (frame < 0) {
		/* Draw the whole thing regardless of frames. */
		height = image->height * image->frames;
		frame = 0;
	} else {
		/* Draw the given frame. */
		height = image->height;
		frame = frame % image->frames;
	}
	width = image->width;

	dstrect.x = x;
	dstrect.y = y;
	dstrect.w = width;
	dstrect.h = height;

	srcrect.x = 0;
	srcrect.y = height * frame;
	srcrect.w = width;
	srcrect.h = height;


	SDL_RenderCopy(renderer, image->surface, &srcrect, &dstrect);

}


void visualize_gui::drawrect(int x, int y, int w, int h, struct  color color)
{
    struct color colorsave;
    Uint8 a;

    SDL_GetRenderDrawColor(renderer, &colorsave.r, &colorsave.g, &colorsave.b, &a);
    SDL_Rect dstrect;

    dstrect.x = x;
    dstrect.y = y;
    dstrect.w = w;
    dstrect.h = h;

	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(renderer, &dstrect);
    SDL_SetRenderDrawColor(renderer, colorsave.r, colorsave.g, colorsave.b, a);
}

