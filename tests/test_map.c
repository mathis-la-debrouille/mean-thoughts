#include <criterion/criterion.h>
#include "map.h"

/* Test de la validation de l'extension du fichier */
Test(map, checkFileExtension) {
    cr_assert(checkFileExtension("test.mtmap"), "L'extension .mtmap devrait être valide");
    cr_assert_not(checkFileExtension("test.txt"), "L'extension .txt ne devrait pas être valide");
}

/* Test d'allocation de la carte */
Test(map, allocateMap) {
    Map *map = allocateMap();
    cr_assert_not_null(map, "L'allocation de la carte a échoué");
    destroyMap(map);
}

/* Test de lecture d'un fichier map.mtmap et ses metadata */
Test(map, newMap_valid_file) {
    Map *map = newMap("maps/map1.mtmap");
    cr_assert_not_null(map, "L'objet Map ne devrait pas être NULL");
    cr_assert_eq(map->width, 30, "La largeur de la carte est incorrecte");
    cr_assert_eq(map->height, 30, "La hauteur de la carte est incorrecte");
    cr_assert_str_eq(map->name, "Maison1", "Le nom de la carte est incorrect");
    cr_assert_str_eq(map->author, "MathisDev", "L'auteur de la carte est incorrect");
    cr_assert_str_eq(map->version, "1.0", "La version de la carte est incorrecte");
    cr_assert_str_eq(map->description, "Map de test", "La description de la carte est incorrecte");
    cr_assert_str_eq(map->texturePath, "assets/map", "Le chemin des textures est incorrect");
    destroyMap(map);
}
