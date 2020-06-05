/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** initialize how to play menu
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include "my.h"
#include "game.h"
#include "menus.h"

static void set_how_to_pos(how_to_play_t *menu, sfRenderWindow *window,
sfView *view)
{
    sfVector2f pos = sfRenderWindow_mapPixelToCoords(window,
    (sfVector2i){800, 900}, view);

    sfSprite_setPosition(menu->button->sprite, pos);
    pos.x -= 800;
    pos.y -= 900;
    sfSprite_setPosition(menu->sprite, pos);
}

static void how_to_event(game_t *game, sfEvent *event, sfRenderWindow *window)
{
    while (sfRenderWindow_pollEvent(window, event)) {
        if (event->type == sfEvtClosed) {
            sfRenderWindow_close(window);
            return;
        }
        if (event->type == sfEvtMouseButtonPressed && event->mouseButton.button == sfMouseLeft) {
            clicked_check(game->menus->how_to->button, window);
            return;
        }
    }
    return;
}

void how_to_play(game_t *game, sfRenderWindow *window)
{
    sfEvent event;

    sfRenderWindow_setView(window, game->main_view);
    set_how_to_pos(game->menus->how_to, window, game->main_view);
    while (game->display == HOW_TO && sfRenderWindow_isOpen(window)) {
        sfRenderWindow_clear(window, sfBlack);
        sfRenderWindow_drawSprite(window, game->menus->how_to->sprite, NULL);
        sfRenderWindow_drawSprite(window, game->menus->how_to->button->sprite, NULL);
        sfRenderWindow_display(window);
        how_to_event(game, &event, window);
        if (hover_check(game->menus->how_to->button, window, &event) == 1)
            game->display = MAIN_MENU;
    }
}

how_to_play_t *init_how_to(void)
{
    how_to_play_t *menu = malloc(sizeof(how_to_play_t));

    if (!menu)
        return (NULL);
    menu->texture = sfTexture_createFromFile("src/media/how_to_play.png", NULL);
    menu->sprite = sfSprite_create();
    menu->button = init_button("src/media/exit.png", (sfVector2f){1500, 800}, (sfIntRect){0, 0, 160, 75});
    if (!menu->texture || !menu->sprite || !menu->button)
        return (NULL);
    sfSprite_setTexture(menu->sprite, menu->texture, sfTrue);
    sfSprite_setScale(menu->sprite, (sfVector2f){1.95, 1.65});
    sfSprite_setPosition(menu->sprite, (sfVector2f){0, 0});
    return (menu);
}

void destroy_how_to(how_to_play_t *menu)
{
    destroy_button(menu->button);
    sfTexture_destroy(menu->texture);
    sfSprite_destroy(menu->sprite);
    free(menu);
}