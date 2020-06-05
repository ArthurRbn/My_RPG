/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** player object
*/

#ifndef PLAYER_H_
#define PLAYER_H_

#include <SFML/Graphics.h>
#include "button.h"
#include "maps.h"
#include "enemy.h"

typedef struct states_s
{
    sfSprite *sprite;
    sfTexture *texture;
    sfSprite *calm;
    sfTexture *texture_fight;
    sfSprite *fight;
    int dir;
    int attack;
    struct states_s *next;
} states_t;

typedef struct stat_s
{
    int lvl;
    int xp;
    int hp;
    int max_hp;
    int damage;
} stat_t;

typedef struct player_s
{
    char *name;
    stat_t *stats;
    float refresh;
    float attack_time;
    states_t *img;
    states_t *states;
} player_t;

typedef struct choose_player_s
{
    player_t *boy;
    player_t *girl;
    sfText *text;
    sfTexture *texture;
    sfSprite *backgrond;
} choose_player_t;

player_t *init_player(char *folder, char *name);
stat_t *init_stats(void);
float get_blocked_direction(sfSprite *player, sfSprite *obj, int id);
void destroy_state(states_t *state);
void destroy_player(player_t *player);
void enemy_attack(enemy_t *enemy, player_t *player);

#endif /* !PLAYER_H_ */