CC = gcc
CFLAGS = -Wall -Wextra -I./ -I/usr/include/SDL2 -D_REENTRANT
LDFLAGS = -lSDL2 -lSDL2_image

SRC = honda_icsim.c canlib.c graphics.c input.c real_can_data.c
OBJ = $(SRC:.c=.o)
EXEC = honda_icsim

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)

install:
	cp $(EXEC) /usr/local/bin/

uninstall:
	rm -f /usr/local/bin/$(EXEC)

.PHONY: all clean install uninstall
