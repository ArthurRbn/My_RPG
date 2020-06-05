/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** non player characters
*/

#ifndef NPC_H_
#define NPC_H_

#include <SFML/Graphics.h>
#include "inventory.h"

typedef struct npc_s
{
    sfTexture *texture_npc;
    sfSprite *sprite_npc;
    sfTexture *texture_icon;
    sfSprite *sprite_icon;
    sfVector2f pos;
    char *name;
    char **dialog;
    float refresh;
    float timer;
    int state;
    int visited;
    item_t *item;
    struct npc_s *next;
} npc_t;

typedef struct dialog_s
{
    sfTexture *texture;
    sfSprite *sprite;
    sfText *line1;
    sfText *line2;
    sfFont *font;
    float refresh;
    int line;
    npc_t *npc;
} dialog_t;

#endif /* !NPC_H_ */