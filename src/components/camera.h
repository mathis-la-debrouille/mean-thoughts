#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <SDL2/SDL.h>

typedef struct {
    float x, y, z;
} Camera;

/**
 * @brief Initialise une caméra à une position donnée.
 */
Camera *createCamera(float x, float y, float z);

/**
 * @brief Modifie la position de la caméra.
 */
void moveCamera(Camera *camera, float dx, float dy, float dz);

/**
 * @brief Calcule le facteur d’échelle en fonction de la distance Z.
 */
float getCameraScale(Camera *camera);

/**
 * @brief Transforme un point en fonction de la caméra.
 */
SDL_Point transformPoint(SDL_Point original, Camera *camera);

/**
 * @brief Libère la mémoire de la caméra.
 */
void destroyCamera(Camera *camera);

#endif // __CAMERA_H__
