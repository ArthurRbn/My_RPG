/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** enemies
*/

#ifndef ENEMY_H_
#define ENEMY_H_

#include <SFML/Graphics.h>
#include "maps.h"

typedef struct states_enemy_s
{
    sfSprite *sprite;
    sfTexture *texture;
    int dir;
    struct states_enemy_s *next;
} states_enemy_t;

typedef struct enemy_s
{
    states_enemy_t *states;
    states_enemy_t *img;
    int damages;
    int hp;
    int max_hp;
    float refresh;
    float attack;
    float respawn;
    int alive;
    int idle_x;
    int idle_y;
    struct enemy_s *next;
} enemy_t;

enemy_t *init_enemies(void);
void init_enemy_stats(enemy_t *new, int hp, int damages);
void display_enemies(enemy_t *enemy, sfRenderWindow *window, sfSprite *player);
void enemy_standby(enemy_t *enemy, block_t ***obj);
void translation(int dir, int x, int y, enemy_t *enemy);
void handle_respawn(enemy_t *enemy);
void remove_all_enemies(enemy_t *enemy);

#endif /* !ENEMY_H_ */