#include "input.h"
#include <SDL2/SDL.h>

void handle_input(int *running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            *running = 0;
        }
    }
}
