#include <iostream>
#include "world.h"
#include "visualize.h"
#include "visualize_gui.h"
#include "appconfig.h"
#include <unistd.h>

int main(int argc, char **argv)
{
    
    World myWorld;
    visualize* myVis;
    appconfig simconfig;
    
    myVis = new visualize_gui();

    //Load media
    if( !myVis->init() )
    {
            std::cerr<< "Failed to initialize visualization!\n";
            return 1;
    }
    
    //Load media
    if( !myVis->load_media(simconfig) )
    {
            std::cerr<< "Failed to load media!\n";
            return 1;
    }
    
    //main simulation loop - everything happens here
    bool quit = false;
    while( quit == false )
    {
        quit = myVis->check_exit();
        myWorld.run_world();
        myVis->draw(myWorld);
        
        //slow down
        usleep(1000);
    }
    
    delete(myVis);
    
    return 0;

}
