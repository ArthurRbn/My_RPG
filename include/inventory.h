/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** inventory and items elements
*/

#ifndef INVENTORY_H_
#define INVENTORY_H_

#include <SFML/Graphics.h>

#define HEAL 0
#define XP 1
#define INV_SIZE 6
#define LVL_FIELD 2
#define DMG_FIELD 3

typedef struct item_s
{
    sfSprite *sprite;
    sfTexture *texture;
    int type;
    struct item_s *next;
} item_t;

typedef struct inventory_s
{
    item_t *item;
    sfVector2f pos;
} inventory_t;

void destroy_item(item_t *item);

#endif /* !INVENTORY_H_ */