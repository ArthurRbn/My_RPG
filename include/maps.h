/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** maps
*/

#ifndef MAPS_H_
#define MAPS_H_

#include <SFML/Graphics.h>

typedef struct block_s
{
    sfTexture *texture;
    sfSprite *sprite;
    int id;
} block_t;

typedef struct map_s
{
    char *name;
    sfIntRect borders;
    sfTexture *texture;
    sfSprite *map;
    block_t ***obj;
} map_t;

map_t *init_map(char *file);
block_t ***init_objects(char *file);
sfIntRect set_rect(float height, float width);
void free_map(map_t *map);

#endif /* !MAPS_H_ */