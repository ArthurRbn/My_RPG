/*
** EPITECH PROJECT, 2020
** MUl_my_rpg_2019
** File description:
** pause menu
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include "game.h"
#include "menus.h"
#include "button.h"

int pause_event(game_t *game, sfEvent *event, sfRenderWindow *window)
{
    while (sfRenderWindow_pollEvent(window, event)) {
        if (event->type == sfEvtClosed) {
            sfRenderWindow_close(window);
            return (3);
        }
        if (event->type == sfEvtMouseButtonPressed &&
        event->mouseButton.button == sfMouseLeft) {
            clicked_check(game->menus->pause->main_menu, window);
            clicked_check(game->menus->pause->quit, window);
            clicked_check(game->menus->pause->resume, window);
            clicked_check(game->menus->pause->settings, window);
            return (0);
        }
    }
    return (0);
}

void display_pause(pause_menu_t *menu, sfRenderWindow *window, game_t *game)
{
    sfRenderWindow_clear(window, sfBlack);
    display_elements(game->map, window, game);
    sfRenderWindow_drawSprite(window, menu->bg, NULL);
    sfRenderWindow_drawSprite(window, menu->main_menu->sprite, NULL);
    sfRenderWindow_drawSprite(window, menu->quit->sprite, NULL);
    sfRenderWindow_drawSprite(window, menu->resume->sprite, NULL);
    sfRenderWindow_drawSprite(window, menu->settings->sprite, NULL);
    sfRenderWindow_display(window);
}

void pause_menu(game_t *game, sfRenderWindow *window)
{
    sfEvent event;

    sfRenderWindow_setView(window, game->main_view);
    set_pause_positions(game->menus->pause, window, game->main_view);
    while (game->display == PAUSE_MENU && sfRenderWindow_isOpen(window)) {
        display_pause(game->menus->pause, window, game);
        pause_event(game, &event, window);
        if (hover_check(game->menus->pause->main_menu, window, &event) == 1)
            game->display = MAIN_MENU;
        if (hover_check(game->menus->pause->quit, window, &event) == 1)
            game->display = QUIT;
        if (hover_check(game->menus->pause->resume, window, &event) == 1)
            game->display = GAME;
        if (hover_check(game->menus->pause->settings, window, &event) == 1) {
            game->display = SETTINGS;
            settings_menu(game, window, &event);
        }
    }
}