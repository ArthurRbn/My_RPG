/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** destroy player elements
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include "player.h"
#include "my.h"

void destroy_state(states_t *state)
{
    sfTexture_destroy(state->texture);
    sfTexture_destroy(state->texture_fight);
    sfSprite_destroy(state->sprite);
    sfSprite_destroy(state->fight);
    free(state);
}

void destroy_player(player_t *player)
{
    states_t *prev = player->states;

    while (player->states) {
        prev = player->states;
        player->states = player->states->next;
        destroy_state(prev);
    }
    free(player->name);
    free(player->stats);
    free(player);
}