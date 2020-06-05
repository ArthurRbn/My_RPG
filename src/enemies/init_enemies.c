/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** initialize enemies
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include "enemy.h"
#include "my.h"

states_enemy_t *create_state_enemy(char *sprite, states_enemy_t *next, int x,
int y)
{
    states_enemy_t *state = malloc(sizeof(states_t));
    sfVector2f pos = set_vector(x, y);

    if (!state)
        return (NULL);
    state->texture = sfTexture_createFromFile(sprite, NULL);
    state->sprite = sfSprite_create();
    if (!state->sprite || !state->texture)
        return (NULL);
    sfSprite_setTexture(state->sprite, state->texture, sfTrue);
    sfSprite_setPosition(state->sprite, pos);
    state->next = next;
    return (state);
}

states_enemy_t *get_enemy_sprites(int x, int y, char *file)
{
    states_enemy_t *ch_list = NULL;
    char **config = get_file(file);
    int i = 0;

    if (!config)
        return (NULL);
    while (config[i] != NULL) {
        ch_list = create_state_enemy(config[i], ch_list, x, y);
        if (!ch_list)
            return (NULL);
        ch_list->dir = i;
        ++i;
    }
    free_tab(config);
    return (ch_list);
}

void set_enemy_scale_n_rect(enemy_t *enemy)
{
    sfIntRect rect = set_rect(17, 17);
    sfVector2f scale = set_vector(2, 2);
    states_enemy_t *temp = enemy->states;

    while (temp) {
        sfSprite_setScale(temp->sprite, scale);
        sfSprite_setTextureRect(temp->sprite, rect);
        sfSprite_setOrigin(temp->sprite, set_vector(9, 9));
        temp = temp->next;
    }
}

enemy_t *init_enemy(char *config, enemy_t *next)
{
    enemy_t *new = malloc(sizeof(enemy_t));
    char **detail = str_to_array(config);
    states_enemy_t *temp = NULL;

    if (!new || !config || !detail)
        return (NULL);
    init_enemy_stats(new, my_getnbr(detail[2]), my_getnbr(detail[3]));
    new->states = get_enemy_sprites(my_getnbr(detail[0]), my_getnbr(detail[1]), detail[4]);
    if (!new->states)
        return (NULL);
    set_enemy_scale_n_rect(new);
    temp = new->states;
    new->img = temp;
    new->next = next;
    free_tab(detail);
    return (new);
}

enemy_t *init_enemies(void)
{
    char **config = get_file("src/media/enemies_list.txt");
    enemy_t *list = NULL;

    if (!config)
        return (NULL);
    for (int i = 0; config[i] != NULL; ++i) {
        list = init_enemy(config[i], list);
        if (!list)
            return (NULL);
    }
    free_tab(config);
    return (list);
}