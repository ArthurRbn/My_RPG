/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** main functions
*/

#include <stdlib.h>
#include <time.h>
#include <SFML/Graphics.h>
#include "my.h"
#include "game.h"

void display(game_t *game, sfRenderWindow *window)
{
    manage_view(game, window);
    set_ui(game, window);
    sfRenderWindow_clear(window, sfBlack);
    sfRenderWindow_setView(window, game->main_view);
    display_elements(game->map, window, game);
    sfRenderWindow_drawSprite(window, game->minimap->sprite, NULL);
    display_ui(game, window);
    sfRenderWindow_setView(window, game->minimap->view);
    display_elements(game->map, window, game);
    sfRenderWindow_display(window);
    if (game->player->stats->hp <= 0)
        restart_game(game, window);
}

void refresh_elements(game_t *game, sfRenderWindow *window, sfEvent *event)
{
    npc_t *temp = game->npc;

    check_npc(game, window, event);
    refresh_enemies(game);
    refresh_player(game->player, game->enemies, game);
    set_sprites_positions(game->player, game->enemies);
    refresh_all_px(game);
    while (temp) {
        move_icon(game->npc);
        temp = temp->next;
    }
    while (destroy_old_particles(&game->particles) == 1);
    destroy_px_particle(&game->effects);
}

void game_loop(sfEvent *event, game_t *game, sfRenderWindow *window)
{
    main_menu(game, window, event);
    sfMusic_stop(game->sounds->soundtrack1);
    sfMusic_play(game->sounds->soundtrack2);
    while (game->display == GAME && sfRenderWindow_isOpen(window)) {
        handle_event(event, window, game);
        clocked_event(game);
        sfClock_restart(game->clock);
        refresh_elements(game, window, event);
        display(game, window);
    }
    if (game->display != QUIT && sfRenderWindow_isOpen(window) == sfTrue)
        game_loop(event, game, window);
}