// #include <SDL2/SDL.h>
#include "game.h"
#include "renderer.h"
#include "map.h"
#include "camera.h"
#include "entity.h"

#include <stdbool.h>

static void handlePlayerInput(Entity *player, const Uint8 *keystate) {
    float speed = 2.0f;

    if (!player)
        return;

    player->dx = 0; 
    player->dy = 0;

    if (keystate[SDL_SCANCODE_W])
        player->dy = -speed;
    if (keystate[SDL_SCANCODE_S])
        player->dy = speed;
    if (keystate[SDL_SCANCODE_A])
        player->dx = -speed;
    if (keystate[SDL_SCANCODE_D])
        player->dx = speed;
}

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

    Entities *entities = createEntities();

    addEntity(entities, 100, 100, ENTITY_PLAYER);
    addEntity(entities, 200, 150, ENTITY_FRIENDLY);
    addEntity(entities, 300, 250, ENTITY_HOSTILE);
    addEntity(entities, 400, 300, ENTITY_NEUTRAL);

    while (running)
    {
        keystate = SDL_GetKeyboardState(NULL);

        if (keystate[SDL_SCANCODE_Q])
            moveCamera(camera, 0.0f, 0.0f, -0.1f); 
        if (keystate[SDL_SCANCODE_E])
            moveCamera(camera, 0.0f, 0.0f, 0.1f);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

        handlePlayerInput(entities->player, keystate);

        updateEntities(entities, map);

        centerCameraOnPoint(camera, entities->player->x, entities->player->y, 800, 600);

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = 0;
            }
        }

        SDL_RenderClear(renderer);
        renderWalls(map, renderer, camera);
        renderEntities(renderer, entities, camera);
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    destroyMap(map);
    destroyEntities(entities);
    destroyCamera(camera);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
