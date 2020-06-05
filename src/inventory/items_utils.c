/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** utils for item managing
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include "game.h"
#include "inventory.h"

void destroy_item(item_t *item)
{
    sfTexture_destroy(item->texture);
    sfSprite_destroy(item->sprite);
    free(item);
}