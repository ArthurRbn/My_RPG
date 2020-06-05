/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** initalize items
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include "my.h"
#include "game.h"
#include "npc.h"
#include "inventory.h"

static void dialog_item(game_t *game, sfRenderWindow *window, sfEvent *event)
{
    int state = 0;
    sfTime timer;
    float time = 0;

    while (state == 0 && sfRenderWindow_isOpen(window) == sfTrue) {
        place_ui(window, game);
        display_dialog(game->dialog, window, game);
        event_handling_dialog(game->dialog, event, window);
        sfClock_restart(game->clock);
        while (state == 0 && time < 150) {
            timer = sfClock_getElapsedTime(game->clock);
            time = timer.microseconds / 10000;
        }
        break;
    }
    reset_dialog(game);
}

static void set_item_text(inventory_t **inv, game_t *game, int i)
{
    char *txt1;
    char *txt2;

    if (inv[i]->item->type == HEAL) {
        txt1 = "Voila un potion de vie,";
        txt2 = "Ca restaurera ta vie";
    } else if (inv[i]->item->type == XP) {
        txt1 = "Voila une potion d'XP,";
        txt2 = "Tu va gagner un niveau";
    }
    game->dialog->line1 = create_text(txt1, 0, 0, game->dialog->font);
    game->dialog->line2 = create_text(txt2, 0, 0, game->dialog->font);
}

void item_npc_to_player(inventory_t **inv, npc_t *npc, game_t *game,
sfRenderWindow *window)
{
    int i = 0;
    sfEvent event;

    if (!npc->item)
        return;
    for (i = 0; inv[i]->item != NULL && i < INV_SIZE; ++i);
    if (i < INV_SIZE) {
        inv[i]->item = npc->item;
        npc->item = NULL;
        set_item_text(inv, game, i);
        dialog_item(game, window, &event);
    }

}

static void item_to_npc(npc_t *npc, char **detail)
{
    if (my_strcmp(npc->name, detail[0]) == 1) {
        npc->item = malloc(sizeof(item_t));
        if (!npc->item)
            return;
        npc->item->texture = sfTexture_createFromFile(detail[1], NULL);
        npc->item->sprite = sfSprite_create();
        if (!npc->item->sprite || !npc->item->texture)
            return;
        sfSprite_setTexture(npc->item->sprite, npc->item->texture, sfTrue);
        sfSprite_setScale(npc->item->sprite, (sfVector2f){3, 3});
        npc->item->type = my_getnbr(detail[2]);
        npc->item->next = NULL;
    }
}

void get_items(npc_t *ch_npc)
{
    char **items_list = get_file("src/media/items_list.txt");
    char **temp = NULL;

    if (!items_list)
        return;
    for (int i = 0; items_list[i] != NULL; ++i) {
        temp = str_to_array(items_list[i]);
        if (!temp)
            return;
        for (npc_t *temp_npc = ch_npc; temp_npc; temp_npc = temp_npc->next) {
            item_to_npc(temp_npc, temp);
        }
        free(temp);
    }
}