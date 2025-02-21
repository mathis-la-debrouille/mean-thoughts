// #include <SDL2/SDL.h>
#include "game.h"
#include "renderer.h"
#include "map.h"
#include "camera.h"

#include <stdbool.h>

void game_loop(void)
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;
    int running = 1;

    init_renderer(&window, &renderer);

    Map *map = newMap("maps/map1.mtmap");
    Camera *camera = createCamera(0, 0, 0);

    printf("------- Map infos -------\n");
    printf("Width: %d\n", map->width);
    printf("Height: %d\n", map->height);
    printf("Name: %s\n", map->name);
    printf("Author: %s\n", map->author);
    printf("Version: %s\n", map->version);
    printf("Description: %s\n", map->description);
    printf("Texture Path: %s\n", map->texturePath);
    
    const Uint8 *keystate;

    while (running)
    {

        keystate = SDL_GetKeyboardState(NULL);
        if (keystate[SDL_SCANCODE_W]) moveCamera(camera, 0.0f, -5.0f, 0.0f);
        if (keystate[SDL_SCANCODE_S]) moveCamera(camera, 0.0f, 5.0f, 0.0f);
        if (keystate[SDL_SCANCODE_A]) moveCamera(camera, -5.0f, 0.0f, 0.0f);
        if (keystate[SDL_SCANCODE_D]) moveCamera(camera, 5.0f, 0.0f, 0.0f);
        if (keystate[SDL_SCANCODE_Q]) moveCamera(camera, 0.0f, 0.0f, -0.1f); 
        if (keystate[SDL_SCANCODE_E]) moveCamera(camera, 0.0f, 0.0f, 0.1f);


        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = 0;
            }
        }

        SDL_RenderClear(renderer);

        renderWalls(map, renderer, camera);
        
        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
