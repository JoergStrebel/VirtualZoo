# VirtualZoo
A simulator for growing artificially intelligent organisms.

* Please see [Computer Consciousness](computer_consciousness.md) for the motivation of this project.
* Please see [Organism Design](organism_design.md) for the design principles and the assumptions / limitations of the simulation design.
* [TODO list](TODO.md) for project

# Prerequisites
- CGAL should be provided by the package manager of the Linux distribution. 
- SDL and SDL_image have build dependencies - see https://wiki.libsdl.org/SDL3/README-linux#build-dependencies for needed packages.
- C++ v17 is a prerequisite
- The git repos of SDL2 and SDL2_Image have to be soft-linked into the root folder.

# Build instructions

Standard cmake workflow:
```shell
mkdir build
cd build
cmake ..
make
```

# References
* Beetle PNG file was downloaded from https://www.pngwing.com/en/free-png-xyjou
* Bush PNG was downloaded from https://clipart-library.com/clipart/bushes-cliparts-3.htm 

