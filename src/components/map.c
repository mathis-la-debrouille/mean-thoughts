#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "map.h"
#include "camera.h"

#define MAX_LINE_LENGTH 1024

static bool computeMapDimensions(FILE *file, size_t *width, size_t *height);
static bool allocateMapData(Map *map);
static void parseMapMetadata(Map *map, FILE *file);
static void parseMapTiles(Map *map, FILE *file);

/**
 * @brief Crée une nouvelle carte à partir d'un fichier
 * @param path Chemin du fichier .mtmap
 * @return Pointeur vers l'objet Map ou NULL en cas d'échec
 */
Map *newMap(const char *path) {
    FILE *file;
    Map *map;
    size_t width = 0, height = 0;

    if (!checkFileExtension(path)) {
        fprintf(stderr, "Erreur : Le fichier %s n'a pas l'extension .mtmap\n", path);
        return NULL;
    }

    file = fopen(path, "r");
    if (!file) {
        fprintf(stderr, "Erreur : Impossible d'ouvrir le fichier %s\n", path);
        return NULL;
    }

    map = allocateMap();
    if (!map) {
        fclose(file);
        return NULL;
    }

    parseMapMetadata(map, file);
    if (!computeMapDimensions(file, &width, &height)) {
        free(map);
        fclose(file);
        return NULL;
    }

    map->width = (int)width;
    map->height = (int)height;

    if (!allocateMapData(map)) {
        free(map);
        fclose(file);
        return NULL;
    }

    parseMapTiles(map, file);
    generateWallPoints(map);
    generateCollisionPoints(map);
    fclose(file);
    return map;
}

/**
 * @brief Vérifie que le fichier possède bien l'extension .mtmap
 * @param path Chemin du fichier
 * @return true si l'extension est correcte, false sinon
 */
bool checkFileExtension(const char *path) {
    const char *ext = strrchr(path, '.');

    return ext && strcmp(ext, ".mtmap") == 0;
}

/**
 * @brief Alloue et initialise une structure Map
 * @return Pointeur vers l'objet Map ou NULL en cas d'échec
 */
Map *allocateMap(void) {
    Map *map = (Map *)malloc(sizeof(Map));

    if (!map) {
        fprintf(stderr, "Erreur : Échec de l'allocation de la carte\n");
        return NULL;
    }
    memset(map, 0, sizeof(Map));
    return map;
}

/**
 * @brief Détermine les dimensions de la carte en comptant les lignes et la largeur
 * @param file Fichier déjà ouvert
 * @param width Pointeur vers la largeur de la carte
 * @param height Pointeur vers la hauteur de la carte
 * @return true si les dimensions ont été calculées, false en cas d'erreur
 */
static bool computeMapDimensions(FILE *file, size_t *width, size_t *height) {
    long pos = ftell(file);
    char line[MAX_LINE_LENGTH];
    *width = 0;
    *height = 0;
    size_t len = 0;

    while (fgets(line, MAX_LINE_LENGTH, file)) {
        len = strlen(line);
        if (len > 1) {
            if (*width == 0) *width = len - 1;
            (*height)++;
        }
    }

    fseek(file, pos, SEEK_SET);
    return (*width > 0 && *height > 0);
}

/**
 * @brief Alloue les structures de données pour stocker les tuiles et la carte de collision
 * @param map Pointeur vers l'objet Map
 * @return true si l'allocation réussit, false en cas d'échec
 */
static bool allocateMapData(Map *map) {
    map->tiles = (char **)malloc((size_t)map->height * sizeof(char *));
    map->collisionMap = (bool **)malloc((size_t)map->height * sizeof(bool *));
    
    if (!map->tiles || !map->collisionMap)
        return false;

    for (size_t i = 0; i < (size_t)map->height; i++) {
        map->tiles[i] = (char *)malloc((size_t)map->width + 1);
        map->collisionMap[i] = (bool *)malloc((size_t)map->width * sizeof(bool));

        if (!map->tiles[i] || !map->collisionMap[i])
            return false;
    }

    return true;
}

/**
 * @brief Analyse les métadonnées de la carte et les stocke dans l'objet Map
 * @param map Pointeur vers l'objet Map
 * @param file Fichier ouvert
 */
static void parseMapMetadata(Map *map, FILE *file) {
    char line[MAX_LINE_LENGTH];
    char *key;
    char *value;

    while (fgets(line, MAX_LINE_LENGTH, file)) {
        if (strncmp(line, "--------------Map--------------", 30) == 0) {
            break;
        }

        key = strtok(line, "=");
        value = strtok(NULL, "\n");

        if (!key || !value)
            continue;
        if (strcmp(key, "Name") == 0) {
            map->name = strdup(value);
        } else if (strcmp(key, "Author") == 0) {
            map->author = strdup(value);
        } else if (strcmp(key, "Version") == 0) {
            map->version = strdup(value);
        } else if (strcmp(key, "Description") == 0) {
            map->description = strdup(value);
        } else if (strcmp(key, "TexturePath") == 0) {
            map->texturePath = strdup(value);
        }
    }
}

/**
 * @brief Lit et stocke les tuiles de la carte
 * @param map Pointeur vers l'objet Map
 * @param file Fichier ouvert à la section des tuiles
 */
static void parseMapTiles(Map *map, FILE *file) {
    char line[MAX_LINE_LENGTH];
    size_t row = 0;

    while (fgets(line, MAX_LINE_LENGTH, file) && row < (size_t)map->height) {
        strncpy(map->tiles[row], line, (size_t)map->width);
        map->tiles[row][map->width] = '\0';

        for (size_t col = 0; col < (size_t)map->width; col++) {
            map->collisionMap[row][col] = (map->tiles[row][col] == 'A');
        }

        row++;
    }
}

/**
 * @brief Libère la mémoire allouée pour une carte
 * @param map Pointeur vers l'objet Map
 */
void destroyMap(Map *map) {
    if (!map)
        return;

    for (size_t i = 0; i < (size_t)map->height; i++) {
        free(map->tiles[i]);
        free(map->collisionMap[i]);
    }

    free(map->tiles);
    free(map->collisionMap);
    free(map->pathName);
    free(map->name);
    free(map->author);
    free(map->version);
    free(map->description);
    free(map->texturePath);
    if (map->wallPoints) {
        for (int i = 0; i < map->height; i++) {
            free(map->wallPoints[i]);
        }
        free(map->wallPoints);
    }
    free(map->wallCounts);
    free(map);
}

#include "map.h"

/**
 * @brief Génère les points de collision de la carte.
 */
void generateCollisionPoints(Map *map) {
    int tileSize = 32;
    int count;

    if (!map)
        return;

    map->collisionPoints = (SDL_Point **)malloc((size_t)map->height * sizeof(SDL_Point *));
    map->collisionCounts = (int *)calloc((size_t)map->height, sizeof(int));

    for (int y = 0; y < map->height; y++) {
        map->collisionPoints[y] = (SDL_Point *)malloc((size_t)map->width * sizeof(SDL_Point));
        count = 0;

        for (int x = 0; x < map->width; x++) {
            if (map->collisionMap[y][x]) {
                map->collisionPoints[y][count++] = (SDL_Point){(int)(x * tileSize), (int)(y * tileSize)};
            }
        }

        map->collisionCounts[y] = count;
    }
}



/**
 * @brief Génère les points des murs en fonction de la carte.
 * @param map Pointeur vers la carte.
 */
void generateWallPoints(Map *map) {
    int tileSize = 32;
    int count = 0;
    int px = 0;
    int py = 0;

    if (!map || !map->tiles)
        return;
    
    map->wallPoints = (SDL_Point **)malloc((size_t)map->height * sizeof(SDL_Point *));
    map->wallCounts = (int *)calloc((size_t)map->height, sizeof(int));
    
    for (int y = 0; y < map->height; y++) {
        map->wallPoints[y] = (SDL_Point *)malloc((size_t)map->width * 4 * sizeof(SDL_Point));
        count = 0;

        for (int x = 0; x < map->width; x++) {
            if (map->tiles[y][x] == 'A') { 
                px = x * tileSize;
                py = y * tileSize;
                map->wallPoints[y][count++] = (SDL_Point){px, py};
                map->wallPoints[y][count++] = (SDL_Point){px + tileSize, py};
                map->wallPoints[y][count++] = (SDL_Point){px + tileSize, py + tileSize};
                map->wallPoints[y][count++] = (SDL_Point){px, py + tileSize};
            }
        }

        map->wallCounts[y] = count;
    }
}

/**
 * @brief Dessine les murs en SDL en utilisant les points générés.
 * @param map Pointeur vers la carte.
 * @param renderer Renderer SDL2 utilisé pour le dessin.
 * @param camera Caméra utilisée pour la transformation des points.
 */
void renderWalls(Map *map, SDL_Renderer *renderer, Camera *camera) {
    if (!map || !map->wallPoints || !renderer || !camera)
        return;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE); // Blanc

    for (int y = 0; y < map->height; y++) {
        for (int i = 0; i < map->wallCounts[y]; i += 4) {
            SDL_Point p1 = transformPoint(map->wallPoints[y][i], camera);
            SDL_Point p2 = transformPoint(map->wallPoints[y][i+1], camera);
            SDL_Point p3 = transformPoint(map->wallPoints[y][i+2], camera);
            SDL_Point p4 = transformPoint(map->wallPoints[y][i+3], camera);

            SDL_RenderDrawLine(renderer, p1.x, p1.y, p2.x, p2.y);
            SDL_RenderDrawLine(renderer, p2.x, p2.y, p3.x, p3.y);
            SDL_RenderDrawLine(renderer, p3.x, p3.y, p4.x, p4.y);
            SDL_RenderDrawLine(renderer, p4.x, p4.y, p1.x, p1.y);
        }
    }
}
