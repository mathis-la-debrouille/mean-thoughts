#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "camera.h"
#include "map.h"

#define MAX_ENTITIES 1000

/**
 * @enum EntityType
 * @brief Définit le type de l'entité.
 */
typedef enum {
    ENTITY_NEUTRAL,
    ENTITY_HOSTILE,
    ENTITY_FRIENDLY,
    ENTITY_PLAYER
} EntityType;

/**
 * @struct Entity
 * @brief Représente une entité sous forme de cercle avec une couleur et un état actif.
 */
typedef struct {
    float x, y;
    float dx, dy;
    EntityType type;
    SDL_Color color;
    bool active;
} Entity;

/**
 * @struct Entities
 * @brief Conteneur global pour la gestion des entités.
 */
typedef struct {
    int maxEntities;
    int numberOfEntities;
    Entity *entities[MAX_ENTITIES];
    Entity *player;
} Entities;

/**
 * @brief Applique le déplacement des entités en fonction de leur vecteur.
 */
void updateEntities(Entities *entities, Map *map);

/**
 * @brief Vérifie la collision entre une entité et la carte.
 */
bool checkCollisionWithMap(Entity *entity, Map *map);

/**
 * @brief Crée une nouvelle entité et lui assigne une couleur.
 */
Entity *createEntity(float x, float y, EntityType type);

/**
 * @brief Définit la couleur de l'entité selon son type.
 */
void setEntityColor(Entity *entity);

/**
 * @brief Dessine un cercle en SDL2.
 */
void drawCircle(SDL_Renderer *renderer, int centerX, int centerY, int radius);

/**
 * @brief Affiche une entité sous forme de cercle en fonction de la caméra.
 */
void renderEntity(SDL_Renderer *renderer, Entity *entity, Camera *camera);

/**
 * @brief Libère la mémoire d'une entité.
 */
void destroyEntity(Entity *entity);

/**
 * @brief Initialise un gestionnaire d'entités.
 */
Entities *createEntities(void);

/**
 * @brief Ajoute une entité au gestionnaire.
 */
Entity *addEntity(Entities *entities, float x, float y, EntityType type);

/**
 * @brief Supprime une entité du gestionnaire.
 */
void removeEntity(Entities *entities, Entity *entity);

/**
 * @brief Affiche toutes les entités en fonction de la caméra.
 */
void renderEntities(SDL_Renderer *renderer, Entities *entities, Camera *camera);

/**
 * @brief Libère la mémoire allouée aux entités.
 */
void destroyEntities(Entities *entities);

#endif // __ENTITY_H__
