/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** init non player characters
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include "game.h"
#include "my.h"
#include "npc.h"

void reset_dialog(game_t *game)
{
    game->dialog->line = 0;
    game->dialog->refresh = 1;
    if (game->dialog->npc->visited == 0)
        create_particles(game, sfTexture_copy(game->dialog->npc->texture_icon), sfSprite_getPosition(game->dialog->npc->sprite_icon));
}

void destroy_npc(npc_t *list)
{
    npc_t *prev = list;

    while (list) {
        prev = list;
        list = list->next;
        free_tab(prev->dialog);
        sfTexture_destroy(prev->texture_icon);
        sfTexture_destroy(prev->texture_npc);
        sfSprite_destroy(prev->sprite_icon);
        sfSprite_destroy(prev->sprite_npc);
        free(prev->name);
        free(prev);
    }
}

void init_npc_sprites(npc_t *new, int x, int y, char *name)
{
    sfIntRect r;

    new->texture_npc = sfTexture_createFromFile(str_concat(name, ".png"), NULL);
    new->texture_icon = sfTexture_createFromFile("src/media/action.png", NULL);
    new->sprite_icon = sfSprite_create();
    new->sprite_npc = sfSprite_create();
    if (!new->sprite_npc || !new->sprite_icon ||!new->texture_icon || !new->texture_icon)
        return;
    sfSprite_setTexture(new->sprite_icon, new->texture_icon, sfTrue);
    sfSprite_setTexture(new->sprite_npc, new->texture_npc, sfTrue);
    sfSprite_setPosition(new->sprite_npc, set_vector(x, y));
    sfSprite_setPosition(new->sprite_icon, set_vector(x, y - 50));
    r = sfSprite_getTextureRect(new->sprite_icon);
    sfSprite_setOrigin(new->sprite_icon, set_vector(r.width / 2, r.height / 2));
    r = sfSprite_getTextureRect(new->sprite_npc);
    sfSprite_setOrigin(new->sprite_npc, set_vector(r.width / 2, r.height / 2));
    sfSprite_setScale(new->sprite_icon, set_vector(1.2f, 1.2f));
    sfSprite_setScale(new->sprite_npc, set_vector(0.6f, 0.6f));
    new->name = my_strdup(name);
}

npc_t *create_npc(char *name, int x, int y, npc_t *next)
{
    npc_t *new_node = malloc(sizeof(npc_t));

    if (!new_node)
        return (NULL);
    init_npc_sprites(new_node, x, y, name);
    new_node->pos = set_vector(x, y);
    new_node->dialog = get_file(str_concat(name, ".dialog"));
    if (!new_node->dialog || !new_node->sprite_npc || !new_node->sprite_icon || !new_node->texture_icon || !new_node->texture_icon)
        return (NULL);
    new_node->refresh = 0;
    new_node->timer = 2000;
    new_node->state = 0;
    new_node->visited = 0;
    new_node->item = NULL;
    new_node->next = next;
    return (new_node);
}

npc_t *init_all_npc(void)
{
    npc_t *list = NULL;
    char **config = get_file("src/media/npc_config.txt");
    char **temp = NULL;

    if (!config)
        return (NULL);
    for (int i = 0; config[i] != NULL; ++i) {
        temp = str_to_array(config[i]);
        if (!temp)
            return (NULL);
        list = create_npc(temp[0], my_getnbr(temp[1]), my_getnbr(temp[2]), list);
        if (!list)
            return (NULL);
        free_tab(temp);
    }
    free_tab(config);
    get_items(list);
    return (list);
}