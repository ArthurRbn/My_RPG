/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** enemies animations
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include "player.h"
#include "enemy.h"
#include "my.h"

void enemy_attack(enemy_t *enemy, player_t *player)
{
    static int count = 0;

    if (enemy->attack > 100) {
        enemy->attack = 0;
        count += 1;
    }
    if (count == 2) {
        player->stats->hp -= enemy->damages;
        count = 0;
    }
}

void display_enemies(enemy_t *enemy, sfRenderWindow *window, sfSprite *player)
{
    enemy_t *temp = enemy;
    sfFloatRect r1 = sfSprite_getGlobalBounds(player);
    sfFloatRect r2;
    sfBool state = sfFalse;

    int i = 0;

    while (temp) {
        if (temp->alive == TRUE && temp->hp > 0) {
            sfRenderWindow_drawSprite(window, temp->img->sprite, NULL);
            r2 = sfSprite_getGlobalBounds(temp->img->sprite);
            state = sfFloatRect_intersects(&r1, &r2, NULL);
            if (state == sfTrue && (r1.top + r1.height) > (r2.top + r2.height))
                sfRenderWindow_drawSprite(window, player, NULL);
        }
        ++i;
        temp = temp->next;
    }
}

void destroy_enemy(enemy_t *enemy)
{
    states_enemy_t *temp = enemy->states->next;
    states_enemy_t *prev = enemy->states;

    sfTexture_destroy(prev->texture);
    sfSprite_destroy(prev->sprite);
    free(prev);
    while (temp) {
        prev = temp;
        temp = temp->next;
        if (prev != NULL) {
            sfTexture_destroy(prev->texture);
            sfSprite_destroy(prev->sprite);
            free(prev);
        }
    }
}

void remove_all_enemies(enemy_t *enemy)
{
    enemy_t *prev = enemy;
    states_enemy_t *prev_state;

    while (enemy) {
        prev = enemy;
        enemy = enemy->next;
        prev_state = prev->states;
        while (prev->states) {
            prev_state = prev->states;
            prev->states = prev->states->next;
            sfSprite_destroy(prev_state->sprite);
            sfTexture_destroy(prev_state->texture);
            free(prev_state);
        }
        free(prev);
    }
}

void handle_respawn(enemy_t *enemy)
{
    enemy_t *temp = enemy;

    while (temp) {
        if (temp->hp <= 0 && temp->alive == TRUE) {
            temp->respawn = 0;
            temp->alive = FALSE;
        } else if (temp->alive == FALSE && temp->respawn > 2000) {
            temp->hp = temp->max_hp;
            temp->alive = TRUE;
        }
        temp = temp->next;
    }
}