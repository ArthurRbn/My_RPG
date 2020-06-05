/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** event handling
*/

#include <SFML/Graphics.h>
#include "game.h"
#include "my.h"
#include "menus.h"

void handle_main_events(sfEvent *event, sfRenderWindow *window, game_t *game)
{
    while (sfRenderWindow_pollEvent(window, event)) {
        if (event->type == sfEvtClosed) {
            sfRenderWindow_close(window);
            return;
        } else if (event->type == sfEvtMouseButtonPressed && event->mouseButton.button == sfMouseLeft) {
            clicked_check(game->menus->start->play, window);
            clicked_check(game->menus->start->quit, window);
            clicked_check(game->menus->start->how_to, window);
            return;
        }
    }
}

int handle_event(sfEvent *event, sfRenderWindow *window, game_t *game)
{
    while (sfRenderWindow_pollEvent(window, event)) {
        if (event->type == sfEvtClosed)
            sfRenderWindow_close(window);
    }
    keyboard_handling(game, window);
    return (0);
}

void event_handling_dialog(dialog_t *dialog, sfEvent *event,
sfRenderWindow *window)
{
    while (sfRenderWindow_pollEvent(window, event)) {
        if (event->type == sfEvtClosed) {
            sfRenderWindow_close(window);
        } else if (event->type == sfEvtMouseButtonPressed || event->type == sfEvtKeyPressed) {
            dialog->refresh = 1;
        }
    }
}

void clocked_event(game_t *game)
{
    sfTime time = sfClock_getElapsedTime(game->clock);

    game->player->refresh += time.microseconds / 10000;
    game->player->attack_time += time.microseconds / 10000;
    for (particle_t *temp = game->particles; temp != NULL; temp = temp->next) {
        temp->time += time.microseconds / 10000;
        temp->refresh += time.microseconds / 10000;
    }
    for (npc_t *npc = game->npc; npc != NULL; npc = npc->next) {
        npc->refresh += time.microseconds / 10000;
        npc->timer += time.microseconds / 10000;
    }
    for (enemy_t *enemy = game->enemies; enemy != NULL; enemy = enemy->next) {
        enemy->refresh += time.microseconds / 10000;
        enemy->attack += time.microseconds / 10000;
        enemy->respawn += time.microseconds / 10000;
    }
    for (px_particle_t *px = game->effects; px != NULL; px = px->next) {
        px->refresh += time.microseconds / 1000;
        px->lifetime += time.microseconds / 1000;
    }
}