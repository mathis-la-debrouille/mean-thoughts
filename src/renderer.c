#include "renderer.h"
#include <stdio.h>

void init_renderer(SDL_Window **window, SDL_Renderer **renderer) {
    *window = SDL_CreateWindow("Platformer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (!*window) {
        printf("Erreur création fenêtre: %s\n", SDL_GetError());
        return;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (!*renderer) {
        printf("Erreur création renderer: %s\n", SDL_GetError());
    }
}
