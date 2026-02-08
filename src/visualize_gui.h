// SPDX-FileCopyrightText: 2023 Jörg Strebel <email>
// SPDX-License-Identifier: Apache-2.0

#ifndef VISUALIZE_GUI_H
#define VISUALIZE_GUI_H
#include <SDL2/SDL.h>
#include <string>
#include <map>
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
    SDL_RendererFlip flip = SDL_FLIP_NONE;

    //Screen dimension constants - we'll always have square screens
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = SCREEN_WIDTH;

    //scaling factors for transforming World coordinates to GUI coordinates
    const float SCALE_WIDTH = static_cast<float>(SCREEN_WIDTH)/static_cast<float>(Constants::MAXX);

    //fixed image size
    const int ICONSIZE = static_cast<int>(std::round(static_cast<float>(Constants::ENTITYSIZE)*SCALE_WIDTH));
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

    std::map<std::string, struct W_Image *> imgrepo;

    SDL_Texture* loadTexture(const std::string &path ) const;
    void drawpoint(unsigned int x, unsigned int y, const struct color& color);
    void clearscreen(void);
    void updatedisplay(void);
    void drawimage(double x, double y, int frame, const struct W_Image *image, double heading);
    void drawrect(int x, int y, int w, int h, const struct color& color);
    std::pair<int,int>  getTextureDetails(SDL_Texture* texture);

};

#endif // VISUALIZE_H
