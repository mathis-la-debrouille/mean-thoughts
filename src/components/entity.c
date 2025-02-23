#include <stdlib.h>
#include "entity.h"
#include "map.h" // Pour gérer les collisions

/**
 * @brief Vérifie si une position est une collision avec la carte.
 */
bool checkCollisionWithMap(Entity *entity, Map *map) {
    int gridX = (int)(entity->x / 32);
    int gridY = (int)(entity->y / 32);

    if (!entity || !map)
        return false;
    if (gridX < 0 || gridY < 0 || gridX >= map->width || gridY >= map->height)
        return true;

    return (map->collisionMap[gridY][gridX] == true);
}

/**
 * @brief Met à jour les entités en appliquant leur déplacement et en gérant les collisions.
 */
void updateEntities(Entities *entities, Map *map) {
    float oldX;
    float oldY;
    Entity *entity;

    if (!entities)
        return;

    for (int i = 0; i < entities->maxEntities; i++) {
        entity = entities->entities[i];
        if (!entity || !entity->active)
            continue;

        oldX = entity->x;
        oldY = entity->y;
        entity->x += entity->dx;
        entity->y += entity->dy;

        if (checkCollisionWithMap(entity, map)) {
            entity->x = oldX;
            entity->y = oldY;
        }
    }
}

/**
 * @brief Crée une nouvelle entité et lui assigne une couleur.
 */
Entity *createEntity(float x, float y, EntityType type) {
    Entity *entity = (Entity *)malloc(sizeof(Entity));

    if (!entity)
        return NULL;

    entity->x = x;
    entity->y = y;
    entity->type = type;
    entity->active = true;
    setEntityColor(entity);

    return entity;
}

/**
 * @brief Définit la couleur de l'entité selon son type.
 */
void setEntityColor(Entity *entity) {
    if (!entity)
        return;

    switch (entity->type) {
        case ENTITY_NEUTRAL:
            entity->color = (SDL_Color){200, 200, 200, 255};
            break;
        case ENTITY_HOSTILE:
            entity->color = (SDL_Color){255, 0, 0, 255};
            break;
        case ENTITY_FRIENDLY:
            entity->color = (SDL_Color){0, 255, 0, 255};
            break;
        case ENTITY_PLAYER:
            entity->color = (SDL_Color){0, 0, 255, 255};
            break;
    }
}

/**
 * @brief Dessine un cercle en SDL2.
 */
void drawCircle(SDL_Renderer *renderer, int centerX, int centerY, int radius) {
    int x = radius;
    int y = 0;
    int err = 1 - x;

    while (x >= y) {
        SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
        SDL_RenderDrawPoint(renderer, centerX + y, centerY + x);
        SDL_RenderDrawPoint(renderer, centerX - y, centerY + x);
        SDL_RenderDrawPoint(renderer, centerX - x, centerY + y);
        SDL_RenderDrawPoint(renderer, centerX - x, centerY - y);
        SDL_RenderDrawPoint(renderer, centerX - y, centerY - x);
        SDL_RenderDrawPoint(renderer, centerX + y, centerY - x);
        SDL_RenderDrawPoint(renderer, centerX + x, centerY - y);
        y++;

        if (err <= 0) {
            err += 2 * y + 1;
        } else {
            x--;
            err += 2 * (y - x) + 1;
        }
    }
}

/**
 * @brief Affiche une entité sous forme de cercle en fonction de la caméra.
 */
void renderEntity(SDL_Renderer *renderer, Entity *entity, Camera *camera) {
    if (!entity || !renderer || !entity->active)
        return;
    SDL_Point transformed = transformPoint((SDL_Point){(int)entity->x, (int)entity->y}, camera);
    int radius = (int)(10 * getCameraScale(camera));

    SDL_SetRenderDrawColor(renderer, entity->color.r, entity->color.g, entity->color.b, entity->color.a);
    drawCircle(renderer, transformed.x, transformed.y, radius);
}

/**
 * @brief Libère la mémoire d'une entité.
 */
void destroyEntity(Entity *entity) {
    if (entity)
        free(entity);
}

/**
 * @brief Crée et initialise un gestionnaire d'entités.
 */
Entities *createEntities(void) {
    Entities *entities = (Entities *)malloc(sizeof(Entities));

    if (!entities)
        return NULL;

    entities->maxEntities = MAX_ENTITIES;
    entities->numberOfEntities = 0;
    entities->player = NULL;

    for (int i = 0; i < MAX_ENTITIES; i++) {
        entities->entities[i] = NULL;
    }

    return entities;
}

/**
 * @brief Ajoute une nouvelle entité au gestionnaire.
 */
Entity *addEntity(Entities *entities, float x, float y, EntityType type) {
    if (!entities || entities->numberOfEntities >= entities->maxEntities)
        return NULL;

    for (int i = 0; i < entities->maxEntities; i++) {
        if (entities->entities[i] == NULL) {
            entities->entities[i] = createEntity(x, y, type);
            if (!entities->entities[i])
                return NULL;

            entities->numberOfEntities++;

            if (type == ENTITY_PLAYER) {
                entities->player = entities->entities[i];
            }

            return entities->entities[i];
        }
    }

    return NULL;
}

/**
 * @brief Supprime une entité et la libère.
 */
void removeEntity(Entities *entities, Entity *entity) {
    if (!entities || !entity)
        return;

    for (int i = 0; i < entities->maxEntities; i++) {
        if (entities->entities[i] == entity) {
            destroyEntity(entities->entities[i]);
            entities->entities[i] = NULL;
            entities->numberOfEntities--;

            if (entities->player == entity) {
                entities->player = NULL;
            }

            return;
        }
    }
}

/**
 * @brief Affiche toutes les entités en fonction de la caméra.
 */
void renderEntities(SDL_Renderer *renderer, Entities *entities, Camera *camera) {
    if (!entities)
        return;

    for (int i = 0; i < entities->maxEntities; i++) {
        if (entities->entities[i]) {
            renderEntity(renderer, entities->entities[i], camera);
        }
    }
}

/**
 * @brief Libère la mémoire du gestionnaire d'entités.
 */
void destroyEntities(Entities *entities) {
    if (!entities)
        return;

    for (int i = 0; i < entities->maxEntities; i++) {
        destroyEntity(entities->entities[i]);
    }

    free(entities);
}
