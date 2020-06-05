/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** actualize statistcs, quests and inventory menu
*/

#include <SFML/Graphics.h>
#include "my.h"
#include "game.h"
#include "quests.h"
#include "menus.h"

static void display_stat_menu(stat_menu_t *menu, sfRenderWindow *window)
{
    sfRenderWindow_clear(window, sfBlack);
    sfRenderWindow_drawSprite(window, menu->background, NULL);
    sfRenderWindow_drawSprite(window, menu->exit->sprite, NULL);
    sfRenderWindow_drawSprite(window, menu->inventory, NULL);
    for (int i = 0; i < INV_SIZE && menu->items && menu->items[i]->item; ++i)
        sfRenderWindow_drawSprite(window, menu->items[i]->item->sprite, NULL);
    for (int i = 0; i < NB_QUESTS && menu->quests && menu->quests[i]; ++i)
        sfRenderWindow_drawText(window, menu->quests[i], NULL);
    for (int i = 0; i < STAT_FIELDS && menu->stats && menu->stats[i]; ++i)
        sfRenderWindow_drawText(window, menu->stats[i], NULL);
    sfRenderWindow_display(window);
}

static void use_item(inventory_t **inv, player_t *player,
sfRenderWindow *window, game_t *game)
{
    for (int i = 0; inv[i]->item != NULL; ++i) {
        if (is_sprite_clicked(inv[i]->item->sprite, window) && inv[i]->item->type == HEAL) {
            destroy_item(inv[i]->item);
            inv[i]->item = NULL;
            player->stats->hp = player->stats->max_hp;
            init_stats_txt(game->menus->stats, window, game->main_view, game);
            sfSound_play(game->sounds->item);
            return;
        } else if (is_sprite_clicked(inv[i]->item->sprite, window) && inv[i]->item->type == XP) {
            destroy_item(inv[i]->item);
            inv[i]->item = NULL;
            player->stats->lvl += 1;
            init_stats_txt(game->menus->stats, window, game->main_view, game);
            sfSound_play(game->sounds->item);
            sfSound_play(game->sounds->lvl_up);
            return;
        }
    }
}

static void stats_event(game_t *game, sfEvent *event, sfRenderWindow *window)
{
    while (sfRenderWindow_pollEvent(window, event)) {
        if (event->type == sfEvtClosed) {
            sfRenderWindow_close(window);
            return;
        } else if (event->type == sfEvtMouseButtonPressed &&
        event->mouseButton.button == sfMouseLeft) {
            clicked_check(game->menus->stats->exit, window);
            use_item(game->menus->stats->items, game->player, window, game);
            return;
        }
    }
}

void stat_menu(game_t *game, sfRenderWindow *window)
{
    sfEvent event;

    sfRenderWindow_setView(window, game->main_view);
    init_stats_txt(game->menus->stats, window, game->main_view, game);
    set_inventory_pos(game->menus->stats, window, game->main_view);
    while (game->display == STAT_MENU && sfRenderWindow_isOpen(window)) {
        display_stat_menu(game->menus->stats, window);
        stats_event(game, &event, window);
        if (hover_check(game->menus->stats->exit, window, &event) == 1)
            game->display = GAME;
    }
}