/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** init maps
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include "my.h"
#include "maps.h"

void get_borders(map_t *map)
{
    sfFloatRect rect;

    rect = sfSprite_getGlobalBounds(map->map);
    map->borders.top = 0;
    map->borders.left = 0;
    map->borders.height = rect.top + rect.height;
    map->borders.width = rect.left + rect.width;
}

map_t *init_map(char *file)
{
    map_t *map = malloc(sizeof(map_t));
    char **tile_path = get_file("src/media/tilespath.txt");

    if (!map)
        return (NULL);
    map->texture = sfTexture_createFromFile("src/media/map_rpg.png", NULL);
    map->map = sfSprite_create();
    if (!map->map || ! map->texture)
        return (NULL);
    sfSprite_setTexture(map->map, map->texture, sfTrue);
    sfSprite_setPosition(map->map, (sfVector2f){0, 0});
    map->name = my_strdup(file);
    map->obj = init_objects(file);
    get_borders(map);
    free_tab(tile_path);
    return (map);
}