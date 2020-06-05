/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** init player
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include "player.h"
#include "enemy.h"
#include "maps.h"
#include "my.h"

states_t *create_state(char *basic_sprite, char *attack_sprite, states_t *next,
int dir)
{
    states_t *state = malloc(sizeof(states_t));
    sfVector2f pos = set_vector(20, 20);

    state->texture = sfTexture_createFromFile(basic_sprite, NULL);
    state->texture_fight = sfTexture_createFromFile(attack_sprite, NULL);
    state->calm = sfSprite_create();
    state->fight = sfSprite_create();
    sfSprite_setTexture(state->calm, state->texture, sfTrue);
    sfSprite_setTexture(state->fight, state->texture_fight, sfTrue);
    sfSprite_setPosition(state->fight, pos);
    sfSprite_setPosition(state->calm, pos);
    state->sprite = state->calm;
    state->dir = dir;
    state->attack = 0;
    state->next = next;
    return (state);
}

states_t *get_player_sprites(char **basic_paths, char **fight_path)
{
    states_t *ch_list = NULL;
    int i = 0;

    while (basic_paths[i] != NULL) {
        ch_list = create_state(basic_paths[i], fight_path[i], ch_list, i);
        ++i;
    }
    return (ch_list);
}

void set_player_scale_n_rect(player_t *player)
{
    sfIntRect basic_rect = set_rect(17, 17);
    sfIntRect fight_rect1 = set_rect(18, 23);
    sfIntRect fight_rect2 = set_rect(18, 16);
    sfVector2f scale = set_vector(3, 3);
    states_t *temp = player->states;
    int i = 0;

    while (temp) {
        sfSprite_setScale(temp->sprite, scale);
        sfSprite_setScale(temp->fight, scale);
        if (i % 2 == 1)
            sfSprite_setTextureRect(temp->fight, fight_rect2);
        else if (i % 2 == 0)
            sfSprite_setTextureRect(temp->fight, fight_rect1);
        sfSprite_setTextureRect(temp->sprite, basic_rect);
        sfSprite_setOrigin(temp->sprite, set_vector(9, 9));
        sfSprite_setOrigin(temp->fight, set_vector(12, 12));
        ++i;
        temp = temp->next;
    }
}

stat_t *init_stats(void)
{
    stat_t *stats = malloc(sizeof(stat_t));

    if (!stats)
        return (NULL);
    stats->lvl = 1;
    stats->xp = 0;
    stats->damage = 50;
    stats->hp = 100;
    stats->max_hp = 100;
    return (stats);
}

player_t *init_player(char *folder, char *name)
{
    player_t *player = malloc(sizeof(player_t));
    char **basic_sprite = get_file(concat_path(folder, "basic_sprite.txt"));
    char **fight_sprite = get_file(concat_path(folder, "fight_sprite.txt"));
    states_t *temp = NULL;

    player->name = my_strdup(name);
    player->stats = init_stats();
    player->refresh = 0;
    player->attack_time = 0;
    player->states = get_player_sprites(basic_sprite, fight_sprite);
    set_player_scale_n_rect(player);
    temp = player->states;
    while (temp && temp->dir != 0)
        temp = temp->next;
    player->img = temp;
    free_tab(basic_sprite);
    free_tab(fight_sprite);
    return (player);
}