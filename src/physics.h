#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>

typedef struct {
  int x, y;
  int vx, vy;
} Player;

void update_player(Player *player);
void draw_player(SDL_Renderer *renderer, Player *player);

#endif
