#include <iostream>
#include "world.h"
#include "visualize.h"
#include "visualize_gui.h"
#include <chrono>
#include <thread>


int main(int argc, char **argv)
{
    
    World myWorld;
    visualize* myVis;
    
    myVis = new visualize_gui();
    
    //Load media
    if( !myVis->init() )
    {
            std::cerr<< "Failed to initialize visualization!\n";
            return 1;
    }
    
    //Load media
    if( !myVis->load_media() )
    {
            std::cerr<< "Failed to load media!\n";
            return 1;
    }
    
    if( !myVis->draw() )
    {
            std::cerr<< "Failed to draw texture!\n";
            return 1;
    }
    
    //std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    
    delete(myVis);
    
    return 0; //implicit conversion
}
