#include <SDL2/SDL.h>
#include "game.h"
#include <stdlib.h>

int main() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("Erreur d'initialisation de SDL: %s\n", SDL_GetError());
        return 1;
    }

    game_loop();

    SDL_Quit();
    return 0;
}