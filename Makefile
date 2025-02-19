CC = clang
CFLAGS = -Wall -Wextra -Werror -I/opt/homebrew/include/
LDFLAGS = -L/opt/homebrew/lib -lSDL2 -lSDL2_image

SRC = src/main.c src/game.c src/player.c src/background.c src/input.c src/renderer.c
OBJ = $(SRC:.c=.o)
EXEC = platformer

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)
