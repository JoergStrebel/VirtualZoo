// SPDX-FileCopyrightText: 2023 Jörg Strebel <email>
// SPDX-License-Identifier: Apache-2.0

#ifndef VISUALIZE_GUI_H
#define VISUALIZE_GUI_H
#include <SDL2/SDL.h>
#include <string>
#include "visualize.h"
#include "appconfig.h"
#include "world.h"


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
    bool load_media(appconfig* values) override;
    
    //draw the scene
    void draw(World myWorld) override;

    //check SDL events
    bool check_exit() override;

    /**
     * Destructor
     */
    ~visualize_gui();

private:
    //The window we'll be rendering to
    SDL_Window* gWindow = NULL;
    

    //Screen dimension constants
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;

    SDL_Renderer *renderer;
    std::string windowtitle = "VirtualZoo World View";

    struct color {
	Uint8 r;
	Uint8 g;
	Uint8 b;
    };

    struct W_Image {
	int width, height;
	int framecount;
	std::string filename;
	SDL_Texture *texture;	/* ptr to SDL texture */
    };

    struct W_Image imgBeetle;

    SDL_Texture* loadTexture( std::string path );
    void drawpoint(unsigned int x, unsigned int y, struct color color);
    void clearscreen(void);
    void updatedisplay(void);
    void drawimage(int x, int y, int frame, struct W_Image *image);
    void drawrect(int x, int y, int w, int h, struct  color color);
    void getTextureDetails(SDL_Texture* texture);

};

#endif // VISUALIZE_H
