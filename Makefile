CC = gcc
CFLAGS = -Wall -Wextra -I. -I/usr/include/SDL2 -D_REENTRANT
LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_gfx

all: honda_icsim

honda_icsim: honda_icsim.o graphics.o input.o real_can_data.o canlib.o
	$(CC) $(CFLAGS) -o honda_icsim honda_icsim.o graphics.o input.o real_can_data.o canlib.o $(LDFLAGS)

clean:
	rm -f *.o honda_icsim

