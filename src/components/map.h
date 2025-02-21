#ifndef __MAP_H__
#define __MAP_H__
#include <stdbool.h>
#include <stdio.h>

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
} Map;



Map *newMap(const char *path);

void destroyMap(Map *map);

bool checkFileExtension(const char *path);

Map *allocateMap(void);

#endif // __MAP_H__
