#include "background.h"
#include <SDL2/SDL_image.h>

void draw_background(SDL_Renderer *renderer, int scroll_offset) {
    SDL_Surface *bg_surface = IMG_Load("assets/backgrounds/layer1.png");
    SDL_Texture *bg_texture = SDL_CreateTextureFromSurface(renderer, bg_surface);

    SDL_Rect dest = { -scroll_offset, 0, 800, 600 };
    SDL_RenderCopy(renderer, bg_texture, NULL, &dest);

    SDL_FreeSurface(bg_surface);
    SDL_DestroyTexture(bg_texture);
}
