// SPDX-FileCopyrightText: 2023 Jörg Strebel <email>
// SPDX-License-Identifier: Apache-2.0

#include "visualize_gui.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include "world.h"
#include "constants.h"
#include <cmath>
#include "locations.h"
#include "location.h"
#include "Point.h"
    
visualize_gui::visualize_gui()
{
                
}

visualize_gui::~visualize_gui()
{
    SDL_Log( "GUI Destructor called");
   //Free loaded image

    //empty map	and free memory
	for (const auto& [key, value] : imgrepo) {		
    	SDL_DestroyTexture( value->texture );    			
	}
	imgrepo.clear();
	
	SDL_Log( "Destroy renderer");
    SDL_DestroyRenderer( renderer );

	SDL_Log( "Destroy window");
	//Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	
	SDL_Log( "Quit SDL subsystems");
	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}


bool visualize_gui::load_media(const appconfig& values)
{            
    bool success = true;
    struct W_Image * tmpimg;
    
    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        SDL_Log( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        success = false;
    }
    
	for(auto const key : values.get_keys())
	{		
		const std::string path = values.get(key);
		SDL_Log( "SDL_image: Loading image: %s\n", path.c_str());
		//Load PNG texture
		SDL_Texture*  gPNGTexture = loadTexture( path );
		if( gPNGTexture == NULL )
		{
			SDL_Log( "Failed to load PNG image!\n" );
			success = false;
		}

    	//store it
    	tmpimg = new struct W_Image();
		tmpimg->texture = gPNGTexture;
    	tmpimg->framecount = 1;

    	const auto txvalue = this->getTextureDetails(gPNGTexture);
    	tmpimg->height = txvalue.second;
    	tmpimg->width = txvalue.first;
    	tmpimg->filename = path;
    	tmpimg->identifier = key;

    	imgrepo[key]=tmpimg;
	}
	return success;
}

std::pair<int,int> visualize_gui::getTextureDetails(SDL_Texture* texture){
     Uint32 format;
    int access, w, h;
    SDL_QueryTexture(texture, &format, &access, &w, &h);
    SDL_Log( "Texture width %i, heigth %i\n", w, h);
    return std::pair<int,int>{w,h};
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


void visualize_gui::draw(World& myWorld)
{
        this->clearscreen();
		
		//redraw the world
		//draw the bushes
		std::vector<Location*> myvec = myWorld.allobjects.getLocations();

		for (Location* loc : myvec) {			
			if (loc->getName()=="bush")
				this->drawimage(loc->getTopLeft().x, loc->getTopLeft().y, 0, imgrepo[loc->getName()], 0);			
		}
		
		//draw the organism
        this->drawimage(myWorld.myOrgMan.x, myWorld.myOrgMan.y, 0, imgrepo["beetle"], myWorld.myOrgMan.heading);
		
        this->updatedisplay();
}

/*
 *
 */
bool visualize_gui::check_exit()
{
    SDL_Event e;
    bool quit = false;

    while( SDL_PollEvent( &e ) )
    {
        if( e.type == SDL_QUIT ) quit = true;
    }

    return quit;
}


bool visualize_gui::init()
{
	Uint32 flags;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
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
 * /parameter frame : index of frame to be drawn; 0-based
 */
void visualize_gui::drawimage(double x, double y, int frame, struct W_Image *image, double heading)
{
	int height, width;
	SDL_Rect srcrect, dstrect;

	if (frame == 0) {
		/* Draw the whole thing regardless of frames. */
		height = image->height * image->framecount;
	} else {
		/* Draw the given frame. */
		height = image->height;
		frame = frame % image->framecount;
	}
	width = image->width;

	dstrect.x = std::round(x);
	dstrect.y = std::round(y);
	dstrect.w = ICONSIZE;
	dstrect.h = ICONSIZE;

	srcrect.x = 0;
	srcrect.y = height * frame;
	srcrect.w = width;
	srcrect.h = height;

	SDL_RenderCopyEx(renderer, image->texture, &srcrect, &dstrect, heading, NULL, flip);
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

