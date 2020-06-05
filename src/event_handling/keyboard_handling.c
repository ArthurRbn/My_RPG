/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** keyboard handling
*/

#include <SFML/Graphics.h>
#include "my.h"
#include "game.h"

static void moving_keys(game_t *game)
{
    if (sfKeyboard_isKeyPressed(sfKeyLeft)) {
        move_player(game, 2);
        return;
    } else if (sfKeyboard_isKeyPressed(sfKeyRight)) {
        move_player(game, 0);
        return;
    }
    if (sfKeyboard_isKeyPressed(sfKeyDown)) {
        move_player(game, 1);
        return;
    } else if (sfKeyboard_isKeyPressed(sfKeyUp)) {
        move_player(game, 3);
        return;
    }
}

void keyboard_handling(game_t *game, sfRenderWindow *window)
{
    moving_keys(game);
    if (sfKeyboard_isKeyPressed(sfKeyA))
        set_attack(game);
    else if (sfKeyboard_isKeyPressed(sfKeyEscape)) {
        game->display = PAUSE_MENU;
        pause_menu(game, window);
    }
    if (sfKeyboard_isKeyPressed(sfKeyE)) {
        game->display = STAT_MENU;
        stat_menu(game, window);
    }
}
