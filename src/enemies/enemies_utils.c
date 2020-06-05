/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** enemies handling utils
*/

#include <SFML/Graphics.h>
#include "my.h"
#include "game.h"
#include "enemy.h"

void init_enemy_stats(enemy_t *new, int hp, int damages)
{
    new->refresh = 0;
    new->hp = hp;
    new->max_hp = hp;
    new->damages = damages;
    new->attack = 0;
    new->respawn = 0;
    new->idle_x = 0;
    new->idle_y = 0;
    new->alive = TRUE;
}