// #include <SDL2/SDL.h>
#include "game.h"
#include "renderer.h"
#include "map.h"

#include <stdbool.h>

void game_loop(void)
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;
    int running = 1;

    init_renderer(&window, &renderer);

    Map *map = newMap("maps/map1.mtmap");

    printf("------- Map infos -------\n");
    printf("Width: %d\n", map->width);
    printf("Height: %d\n", map->height);
    printf("Name: %s\n", map->name);
    printf("Author: %s\n", map->author);
    printf("Version: %s\n", map->version);
    printf("Description: %s\n", map->description);
    printf("Texture Path: %s\n", map->texturePath);
    

    while (running)
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = 0;
            }
        }

        SDL_RenderClear(renderer);

        renderWalls(map, renderer);
        
        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
