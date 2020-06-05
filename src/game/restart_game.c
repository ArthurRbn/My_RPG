/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** restart game
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include "my.h"
#include "quests.h"

static void restart_event(sfRenderWindow *window, sfEvent *event, game_t *game)
{
    while (sfRenderWindow_pollEvent(window, event)) {
        if (event->type == sfEvtClosed) {
            sfRenderWindow_close(window);
        } else if (sfKeyboard_isKeyPressed(sfKeyR)) {
            game->display = MAIN_MENU;
        }
    }
}

void restart_loop(sfRenderWindow *window, game_t *game, sfEvent *event)
{
    char *msg = "You died ! Press R to get back to starting menu";
    sfText *end_msg = create_text(msg, 1, 1, game->dialog->font);
    const sfView *view = sfRenderWindow_getView(window);
    sfVector2f pos;

    pos = sfRenderWindow_mapPixelToCoords(window, (sfVector2i){500, 500}, view);
    sfText_setPosition(end_msg, pos);
    sfRenderWindow_clear(window, sfBlack);
    display_elements(game->map, window, game);
    sfRenderWindow_drawText(window, end_msg, NULL);
    sfRenderWindow_display(window);
    while (game->display == GAME && sfRenderWindow_isOpen(window))
        restart_event(window, event, game);
}

void restart_game(game_t *game, sfRenderWindow *window)
{
    sfEvent event;

    sfRenderWindow_setView(window, game->main_view);
    restart_loop(window, game, &event);
    destroy_effects(game->effects);
    remove_all_enemies(game->enemies);
    destroy_npc(game->npc);
    destroy_quests(game->quests);
    game->enemies = init_enemies();
    game->npc = init_all_npc();
    game->quests = get_quests();
    free(game->player->stats);
    game->player->stats = init_stats();
    sfSprite_setPosition(game->player->img->sprite, (sfVector2f){500, 500});
}