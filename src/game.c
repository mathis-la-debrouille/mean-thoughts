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

    SDL_Point points[5];
    points[0].x = 100;
    points[0].y = 100;
    points[1].x = 200;
    points[1].y = 100;
    points[2].x = 200;
    points[2].y = 200;
    points[3].x = 100;
    points[3].y = 200;   
    points[4].x = 100;
    points[4].y = 100;

    while (running) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderDrawLine(renderer, 0, 0, 800, 600);

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderDrawLines(renderer, points, 5);

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
