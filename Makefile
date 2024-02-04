# Makefile
# for SDL:
#   follow https://wiki.libsdl.org/SDL2/Installation
#  clone somewhere else :)
#   git clone https://github.com/libsdl-org/SDL.git -b SDL2
#   cd SDL
#   mkdir build
#   cd build
#   ../configure
#   make
#   sudo make install
#
# this project also requires SDL2 ttf -> sudo apt install libsdl2-ttf-dev

CC=gcc
CFLAGS=-I/includes
LDFLAGS = -lm `sdl2-config --cflags --libs` -lSDL2_ttf
DEPS = common.h
OBJ = main.o \
	initialization.o \
	grid.o \
	events.o \
	compute.o \
	kernel.o \
	menu.o menu_primordia.o menu_conway.o \
	conway.o lenia.o primordia.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

play: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

re: clean play

clean:
	rm -f *.o play
