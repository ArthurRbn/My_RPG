/*
** EPITECH PROJECT, 2020
** parallax utils
** File description:
** parallax utils
*/

#include <SFML/Graphics.h>
#include "my.h"
#include "game.h"
#include "menus.h"

static void move_parallax(main_menu_t *menu)
{
    sfVector2f pos;

    for (int i = 0; menu->bg[i] != NULL; ++i) {
        pos = sfSprite_getPosition(menu->bg[i]->sprite);
        if (pos.x <= -1920) {
            pos.x = 1920;
            sfSprite_setPosition(menu->bg[i]->sprite, pos);
        }
    }
}

static void move_bg(main_menu_t *menu, game_t *game)
{
    sfVector2f speed = {0, 0};
    static float elapsed = 0;
    sfTime time = sfClock_getElapsedTime(game->clock);

    elapsed += time.microseconds / 10000;
    sfClock_restart(game->clock);
    if (elapsed < 2)
        return;
    else if (elapsed > 2)
        elapsed = 0;
    for (int i = 0; menu->bg[i] != NULL; ++i) {
        if (i % 2 == 0)
            speed.x -= 1;
        sfSprite_move(menu->bg[i]->sprite, speed);
    }
    move_parallax(menu);
}

static void display_main_menu(main_menu_t *menu, sfRenderWindow *window)
{
    sfRenderWindow_clear(window, sfBlack);
    for (int i = 0; menu->bg[i] != NULL; ++i)
        sfRenderWindow_drawSprite(window, menu->bg[i]->sprite, NULL);
    sfRenderWindow_drawSprite(window, menu->play->sprite, NULL);
    sfRenderWindow_drawSprite(window, menu->how_to->sprite, NULL);
    sfRenderWindow_drawSprite(window, menu->quit->sprite, NULL);
    sfRenderWindow_display(window);
}

void main_menu(game_t *game, sfRenderWindow *window, sfEvent *event)
{
    sfMusic_stop(game->sounds->soundtrack2);
    sfMusic_play(game->sounds->soundtrack1);
    sfView_setCenter(game->main_view, (sfVector2f){1920 / 2, 1080 / 2});
    sfRenderWindow_setView(window, game->main_view);
    while (game->display == MAIN_MENU && sfRenderWindow_isOpen(window)) {
        handle_main_events(event, window, game);
        move_bg(game->menus->start, game);;
        display_main_menu(game->menus->start, window);
        if (hover_check(game->menus->start->play, window, event) == 1)
            game->display = GAME;
        if (hover_check(game->menus->start->how_to, window, event) == 1) {
            game->display = HOW_TO;
            how_to_play(game, window);
        }
        if (hover_check(game->menus->start->quit, window, event) == 1)
            game->display = QUIT;
    }
}