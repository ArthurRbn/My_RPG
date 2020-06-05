/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** animation of enemies waiting for a fight
*/

#include <SFML/Graphics.h>
#include "my.h"
#include "game.h"
#include "enemy.h"

static void enemy_standby2(enemy_t *enemy, int blocked)
{
    if (enemy->idle_x > 0 && blocked != 0 && blocked != 3) {
        translation(2, -2, 0, enemy);
        enemy->idle_x -= 2;
        return;
    } else if (enemy->idle_y > 0 && blocked != 0 && blocked != 1) {
        translation(3, 0, -2, enemy);
        enemy->idle_y -= 2;
        return;
    }
}

void enemy_standby(enemy_t *enemy, block_t ***obj)
{
    int block = check_colision(enemy->img->sprite, obj);

    if (enemy->idle_x < 60 && enemy->idle_y <= 0 && block != 1 && block != 2) {
        translation(0, 2, 0, enemy);
        enemy->idle_x += 2;
        return;
    } else if (enemy->idle_y < 60 && enemy->idle_x >= 60 && block != 2 && block != 3) {
        translation(1, 0, 2, enemy);
        enemy->idle_y += 2;
        return;
    }
    enemy_standby2(enemy, block);
}