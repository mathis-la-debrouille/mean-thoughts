#include <SDL2/SDL.h>
#include "game.h"
#include "renderer.h"
#include "input.h"

void game_loop() {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;
    int running = 1;

    init_renderer(&window, &renderer);

    while (running) {
        // handle_input(&running);
        SDL_RenderClear(renderer);

        // Set render draw color to white
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

      
        SDL_RenderDrawPoint(renderer, 40, 40);
        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        SDL_Delay(16); 
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
