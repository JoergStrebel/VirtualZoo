// SPDX-FileCopyrightText: 2023 Jörg Strebel <email>
// SPDX-License-Identifier: Apache-2.0

#ifndef VISUALIZE_GUI_H
#define VISUALIZE_GUI_H
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include "visualize.h"
#include "appconfig.h"
#include "world.h"
#include <utility>
#include <cmath>
#include "constants.h"


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
    bool load_media(const appconfig& values) override;
    
    //draw the scene
    void draw(const World& myWorld) override;

    //check SDL events
    bool check_exit() override;

    /**
     * Destructor
     */
    ~visualize_gui();

private:
    //The window we'll be rendering to
    SDL_Window* gWindow = NULL;

    //Screen dimension constants - we'll always have square screens
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = SCREEN_WIDTH;

    //scaling factors for transforming World coordinates to GUI coordinates
    const float SCALE_WIDTH = float(SCREEN_WIDTH)/float(Constants::MAXX);

    //fixed image size
    const int ICONSIZE = (int)std::round(float(Constants::ENTITYSIZE)*SCALE_WIDTH);

    SDL_Renderer *renderer;
    std::string windowtitle = "VirtualZoo World View";

    struct color {
	Uint8 r;
	Uint8 g;
	Uint8 b;
    };


    struct W_Image {
	std::string identifier;
    int width, height;
	int framecount;
	std::string filename;
	SDL_Texture *texture;	/* ptr to SDL texture */
    };

    std::vector<struct W_Image *> imgrepo;

    SDL_Texture* loadTexture( std::string path );
    void drawpoint(unsigned int x, unsigned int y, struct color color);
    void clearscreen(void);
    void updatedisplay(void);
    void drawimage(int x, int y, int frame, struct W_Image *image);
    void drawrect(int x, int y, int w, int h, struct  color color);
    std::pair<int,int>  getTextureDetails(SDL_Texture* texture);

};

#endif // VISUALIZE_H
