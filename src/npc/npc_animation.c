/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** non player characters animation
*/

#include <SFML/Graphics.h>
#include "my.h"
#include "npc.h"

void move_icon(npc_t *npc)
{
    sfVector2f icon_pos;

    if (npc->refresh < 10 || npc->visited == 1)
        return;
    npc->refresh = 0;
    if (npc->state == 0)
        sfSprite_move(npc->sprite_icon, set_vector(0, -1));
    else if (npc->state == 1)
        sfSprite_move(npc->sprite_icon, set_vector(0, +1));
    icon_pos = sfSprite_getPosition(npc->sprite_icon);
    if (icon_pos.y > npc->pos.y - 42)
        npc->state = 0;
    else if (icon_pos.y < npc->pos.y - 50)
        npc->state = 1;
}

void display_npc(npc_t *list, sfRenderWindow *window, sfSprite *player)
{
    npc_t *temp = list;
    sfFloatRect r1 = sfSprite_getGlobalBounds(player);
    sfFloatRect r2;
    sfBool state = sfFalse;

    while (temp) {
        sfRenderWindow_drawSprite(window, temp->sprite_npc, NULL);
        r2 = sfSprite_getGlobalBounds(temp->sprite_npc);
        state = sfFloatRect_intersects(&r1, &r2, NULL);
        if (state == sfTrue && (r1.top + r1.height) > (r2.top + r2.height))
            sfRenderWindow_drawSprite(window, player, NULL);
        if (temp->visited == 0)
            sfRenderWindow_drawSprite(window, temp->sprite_icon, NULL);
        temp = temp->next;
    }
}

void check_npc(game_t *game, sfRenderWindow *window, sfEvent *event)
{
    npc_t *temp = game->npc;
    sfFloatRect rect1 = sfSprite_getGlobalBounds(game->player->img->sprite);
    sfFloatRect rect2;
    sfBool state = sfFalse;

    while (temp && state == sfFalse) {
        rect2 = sfSprite_getGlobalBounds(temp->sprite_npc);
        state = sfFloatRect_intersects(&rect1, &rect2, NULL);
        if (state == sfFalse)
            temp = temp->next;
    }
    if (state == sfTrue && temp->timer > 1000) {
        game->dialog->npc = temp;
        dialog(game, window, event);
        item_npc_to_player(game->menus->stats->items, temp, game, window);
        game->dialog->npc->timer = 0;
        game->dialog->npc->visited = 1;
    }
}