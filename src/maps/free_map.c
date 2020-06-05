/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** free map_t object
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include "maps.h"
#include "my.h"

void free_obj(block_t ***obj)
{
    for (int i = 0; obj[i] != NULL; ++i) {
        for (int j = 0; obj[i][j] != NULL; ++j) {
            sfTexture_destroy(obj[i][j]->texture);
            sfSprite_destroy(obj[i][j]->sprite);
            free(obj[i][j]);
        }
        free(obj[i]);
    }
    free(obj);
}

void free_map(map_t *map)
{
    free(map->name);
    sfTexture_destroy(map->texture);
    sfSprite_destroy(map->map);
    free_obj(map->obj);
    free(map);
}