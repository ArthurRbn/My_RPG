/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** utils to set stats menu
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include "my.h"
#include "game.h"
#include "menus.h"

static sfText **fill_quests_txt(game_t *game, sfVector2f pos, sfText **quests)
{
    quest_slot_t *temp = game->quests;
    char *txt = NULL;

    for (int i = 0; i < NB_QUESTS; ++i) {
        if (temp->active == TRUE)
            txt = str_concat(temp->title, " : not finished");
        else if (temp->active == FALSE)
            txt = str_concat(temp->title, " : finished");
        quests[i] = create_text(txt, pos.x, pos.y, game->dialog->font);
        if (txt != NULL)
            free(txt);
        pos.y += 70;
        temp = temp->next;
    }
    return (quests);
}

static sfText **fill_stat_texts(game_t *game, sfVector2f pos, sfText **stats)
{
    char *txt = NULL;

    txt = str_concat("Health : ", nbr_str(game->player->stats->hp));
    stats[HEAL] = create_text(txt, pos.x, pos.y, game->dialog->font);
    pos.y += 70;
    txt = str_concat("Experience : ", nbr_str(game->player->stats->xp));
    stats[XP] = create_text(txt, pos.x, pos.y, game->dialog->font);
    pos.y += 70;
    txt = str_concat("Level : ", nbr_str(game->player->stats->lvl));
    stats[LVL_FIELD] = create_text(txt, pos.x, pos.y, game->dialog->font);
    pos.y += 70;
    txt = str_concat("Damages : ", nbr_str(game->player->stats->damage));
    stats[DMG_FIELD] = create_text(txt, pos.x, pos.y, game->dialog->font);
    return (stats);
}

static void destroy_old_txt(stat_menu_t *menu)
{
    for (int i = 0; menu->stats != NULL && menu->stats[i] != NULL; ++i) {
        sfText_destroy(menu->stats[i]);
        menu->stats[i] = NULL;
        free(menu->stats);
        menu->stats = NULL;
    }
    for (int i = 0; menu->quests != NULL && menu->quests[i] != NULL; ++i) {
        sfText_destroy(menu->quests[i]);
        menu->quests[i] = NULL;
        free(menu->quests);
        menu->quests = NULL;
    }
}

void init_stats_txt(stat_menu_t *menu, sfRenderWindow *window, sfView *view,
game_t *game)
{
    sfText **stats = malloc(sizeof(sfText *) * STAT_FIELDS);
    sfText **quests = malloc(sizeof(sfText *) * NB_QUESTS);
    sfVector2f pos = sfRenderWindow_mapPixelToCoords(window, (sfVector2i){200, 300}, view);
    sfVector2f pos2 = sfRenderWindow_mapPixelToCoords(window, (sfVector2i){800, 100}, view);

    if (!stats && !quests)
        return;
    destroy_old_txt(menu);
    menu->stats = fill_stat_texts(game, pos, stats);
    menu->quests = fill_quests_txt(game, pos2, quests);
}

void destroy_stat_menu(stat_menu_t *menu)
{
    sfTexture_destroy(menu->t_bg);
    sfTexture_destroy(menu->t_invent);
    sfSprite_destroy(menu->background);
    sfSprite_destroy(menu->inventory);
    destroy_button(menu->exit);
    destroy_old_txt(menu);
    for (int i = 0; i < INV_SIZE; ++i) {
        if (menu->items[i]->item != NULL) {
            sfTexture_destroy(menu->items[i]->item->texture);
            sfSprite_destroy(menu->items[i]->item->sprite);
            free(menu->items[i]->item);
        }
        free(menu->items[i]);
    }
    free(menu->items);
    free(menu);
}