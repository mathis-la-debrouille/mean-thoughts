#include <stdlib.h>
#include "camera.h"

/**
 * @brief Crée une nouvelle caméra avec une position initiale.
 */
Camera *createCamera(float x, float y, float z) {
    Camera *camera = (Camera *)malloc(sizeof(Camera));
    
    if (!camera)
        return NULL;
    camera->x = x;
    camera->y = y;
    camera->z = z;
    return camera;
}

/**
 * @brief Déplace la caméra de `dx, dy, dz`.
 */
void moveCamera(Camera *camera, float dx, float dy, float dz) {
    if (!camera)
        return;

    camera->x += dx;
    camera->y += dy;
    camera->z += dz;
}

/**
 * @brief Retourne un facteur de mise à l'échelle en fonction de `Z`.
 */
float getCameraScale(Camera *camera) {
    if (!camera)
        return 1.0f;
    
    return 1.0f / (1.0f + camera->z * 0.1f); // Plus Z est grand, plus le scale diminue
}

/**
 * @brief Transforme un point selon la caméra.
 */
SDL_Point transformPoint(SDL_Point original, Camera *camera) {
    float scale = getCameraScale(camera);

    return (SDL_Point){
        .x = (int)((original.x - camera->x) * scale),
        .y = (int)((original.y - camera->y) * scale)
    };
}

/**
 * @brief Libère la mémoire de la caméra.
 */
void destroyCamera(Camera *camera) {
    if (camera) free(camera);
}

/**
 * @brief Centre la caméra sur un point donné.
 * @param camera Pointeur vers la caméra.
 * @param targetX Coordonnée X du point cible.
 * @param targetY Coordonnée Y du point cible.
 * @param screenWidth Largeur de l'écran en pixels.
 * @param screenHeight Hauteur de l'écran en pixels.
 */
void centerCameraOnPoint(Camera *camera, float targetX, float targetY, int screenWidth, int screenHeight) {
    if (!camera)
        return;

    float scale = getCameraScale(camera);

    camera->x = targetX - (screenWidth / 2) / scale;
    camera->y = targetY - (screenHeight / 2) / scale;
}
