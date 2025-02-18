#include "player.h"
#include <SDL2/SDL_image.h>

void update_player(Player *player) {
    player->y += player->vy;
}

void draw_player(SDL_Renderer *renderer, Player *player) {
    SDL_Surface *sprite = IMG_Load("assets/sprites/player.png");
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, sprite);

    SDL_Rect dest = { player->x, player->y, 50, 50 };
    SDL_RenderCopy(renderer, texture, NULL, &dest);

    SDL_FreeSurface(sprite);
    SDL_DestroyTexture(texture);
}
