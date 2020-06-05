/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** main
*/

#include <SFML/Graphics.h>
#include <stdio.h>
#include "my.h"
#include "game.h"

int main(int ac, char **av)
{
    sfRenderWindow *window = NULL;
    game_t *game = NULL;
    sfEvent event;

    if (ac != 2) {
        my_putstr("Please start the game with your name as argument\n");
        my_putstr("Usage: ./my_rpg [player_name]\n");
        return (84);
    }
    window = init_window();
    game = init_game(window, &event, av[1]);
    if (!game || !window) {
        my_putstr("Something failed, launch the game again please\n");
        my_putstr("If it happens several times clone the repository again\n");
        return (84);
    }
    game_loop(&event, game, window);
    ultimate_destroy(game, window);
    return (0);
}