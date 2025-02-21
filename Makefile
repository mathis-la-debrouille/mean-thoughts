CC = clang
WARNINGS = -pedantic -Wshadow -Wpointer-arith			\
	-Wcast-align -Wwrite-strings -Wmissing-prototypes	\
	-Wmissing-declarations -Wredundant-decls		\
	-Wnested-externs -Winline -Wno-long-long 		\
	-Wconversion -Wstrict-prototypes

CFLAGS = -Wall \
	-Wextra \
	-Werror \
	$(WARNINGS) \
	-I /opt/homebrew/include/ \
	-I src \
	-I src/components \
	-I src/legacy \
	-I src/utils \
	-std=c17

LDFLAGS = -L/opt/homebrew/lib \
	-lSDL2 \
	-lSDL2_image

TEST_LDFLAGS = -L/opt/homebrew/Cellar/criterion/2.4.2_2/lib/ \
	-L/opt/homebrew/lib \
	-lcriterion \
	-lSDL2 \
	-lSDL2_image

SRC = src/game.c \
	src/background.c \
	src/renderer.c \
	src/legacy/player.c \
	src/legacy/input.c \
	src/legacy/physics.c \
	src/components/map.c \
	src/components/camera.c

TEST_SRC = tests/test_map.c

OBJ = $(SRC:.c=.o)
EXEC = platformer
TEST_EXEC = test

all: $(EXEC)

$(EXEC): $(OBJ) src/main.o
	$(CC) $(CFLAGS) $(OBJ) src/main.o -o $(EXEC) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

tests: $(TEST_SRC)
	$(CC) $(CFLAGS) $(TEST_SRC) $(SRC) -o $(TEST_EXEC) $(TEST_LDFLAGS)

run-tests: tests
	./$(TEST_EXEC)

clean:
	rm -f $(OBJ) $(EXEC) src/main.o

clean-tests:
	rm -f $(TEST_EXEC)

re: clean all
