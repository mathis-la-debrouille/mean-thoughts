#ifndef __MAP_H__
#define __MAP_H__

#include <stdbool.h>
#include <stdio.h>
#include <SDL2/SDL.h>

#include "camera.h"

typedef struct {
    int width;
    int height;
    char **tiles;
    char **renderBuffer;
    bool **collisionMap;
    bool renderDrawLines;
    bool renderDrawCollision;
    bool renderTextures;
    bool renderDrawGrid;
    char *pathName;
    char *name;
    char *author;
    char *version;
    char *description;
    char *texturePath;

    SDL_Point **wallPoints; 
    int *wallCounts;
    SDL_Point **collisionPoints;
    int *collisionCounts;
} Map;

void generateCollisionPoints(Map *map);
Map *newMap(const char *path);
void destroyMap(Map *map);
bool checkFileExtension(const char *path);
Map *allocateMap(void);
void generateWallPoints(Map *map);
void renderWalls(Map *map, SDL_Renderer *renderer, Camera *camera);

#endif // __MAP_H__
