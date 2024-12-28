CC := g++ # This is the main compiler
# CC := clang --analyze # and comment out the linker last line for sanity
SRCDIR := src
BUILDDIR := build
TARGET := bin/simcore
 
SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
#CFLAGS := -g -Wall -Wextra -W -Wconversion -Wdouble-promotion -Wcast-align -Wcast-qual -Wmissing-declarations -Wpointer-arith -Wreturn-type -Wno-unused-parameter \
    -Wno-unused-function -Wno-sign-conversion -fsanitize=undefined -D_GNU_SOURCE -pedantic-errors
CFLAGS := -g -Wall -Wextra -W -Wconversion -Wdouble-promotion -Wcast-align -Wcast-qual -Wmissing-declarations -Wpointer-arith -Wreturn-type -Wno-unused-parameter \
    -Wno-unused-function -Wno-sign-conversion -pedantic-errors `sdl2-config --cflags` -march=native -mtune=native \
    -mfpmath=sse -msse4.1 -msse4.2 -std=c++17

LIB := -pthread -L lib `sdl2-config --libs` -lSDL2_image
INC := -I src

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning..."; 
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)

# Tests
#tester:
#	$(CC) $(CFLAGS) test/tester.cpp $(INC) $(LIB) -o bin/tester

# Spikes
#ticket:
#	$(CC) $(CFLAGS) spikes/ticket.cpp $(INC) $(LIB) -o bin/ticket

.PHONY: clean 
