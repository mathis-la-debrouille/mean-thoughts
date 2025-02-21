#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <SDL2/SDL.h>

/**
 * @struct Camera
 * @brief Structure représentant une caméra dans l'espace 2D avec un effet de profondeur.
 *
 * La caméra est utilisée pour transformer les positions des objets à l'écran en fonction :
 * - **X, Y** : Position de la caméra dans le monde (décalage).
 * - **Z** : Profondeur qui influence la taille des objets (plus Z est élevé, plus l’objet est petit).
 *
 * **Utilisation** :
 * 1. **Créer une caméra** : `Camera *camera = createCamera(0.0f, 0.0f, 0.0f);`
 * 2. **Modifier sa position** : `moveCamera(camera, dx, dy, dz);`
 * 3. **Transformer un point** avant de l'afficher : `SDL_Point p = transformPoint(original, camera);`
 */
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
