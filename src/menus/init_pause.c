/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** initalize pause menu
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include "menus.h"

void set_pause_positions2(pause_menu_t *pause, sfRenderWindow *window,
sfView *view)
{
    sfVector2i relative;
    sfVector2f pos;

    relative.x = 0;
    relative.y = 0;
    pos = sfRenderWindow_mapPixelToCoords(window, relative, view);
    sfSprite_setPosition(pause->bg, pos);
}

void set_pause_positions(pause_menu_t *pause, sfRenderWindow *window,
sfView *view)
{
    sfVector2i relative;
    sfVector2f pos;

    relative.x = pause->main_menu->pos.x;
    relative.y = pause->main_menu->pos.y;
    pos = sfRenderWindow_mapPixelToCoords(window, relative, view);
    sfSprite_setPosition(pause->main_menu->sprite, pos);
    relative.x = pause->quit->pos.x;
    relative.y = pause->quit->pos.y;
    pos = sfRenderWindow_mapPixelToCoords(window, relative, view);
    sfSprite_setPosition(pause->quit->sprite, pos);
    relative.x = pause->resume->pos.x;
    relative.y = pause->resume->pos.y;
    pos = sfRenderWindow_mapPixelToCoords(window, relative, view);
    sfSprite_setPosition(pause->resume->sprite, pos);
    relative.x = pause->settings->pos.x;
    relative.y = pause->settings->pos.y;
    pos = sfRenderWindow_mapPixelToCoords(window, relative, view);
    sfSprite_setPosition(pause->settings->sprite, pos);
    set_pause_positions2(pause, window, view);
}

pause_menu_t *init_pause_menu(void)
{
    pause_menu_t *menu = malloc(sizeof(pause_menu_t));

    if (!menu)
        return (NULL);
    menu->main_menu = init_button("src/media/menu.png", (sfVector2f){900, 300}, (sfIntRect){0, 0, 160, 75});
    menu->quit = init_button("src/media/quit.png", (sfVector2f){899, 600}, (sfIntRect){0, 0, 160, 75});
    menu->resume = init_button("src/media/resume.png", (sfVector2f){901, 400}, (sfIntRect){0, 0, 160, 75});
    menu->settings = init_button("src/media/settings.png", (sfVector2f){905, 500}, (sfIntRect){0, 0, 160, 75});
    menu->texture = sfTexture_createFromFile("src/media/fond_gris.jpg", NULL);
    menu->bg = sfSprite_create();
    sfSprite_setTexture(menu->bg, menu->texture, sfTrue);
    sfSprite_setColor(menu->bg, (sfColor){192, 192, 192, 200});
    return (menu);
}

void destroy_pause_menu(pause_menu_t *menu)
{
    sfTexture_destroy(menu->texture);
    sfSprite_destroy(menu->bg);
    destroy_button(menu->main_menu);
    destroy_button(menu->quit);
    destroy_button(menu->resume);
    destroy_button(menu->settings);
    free(menu);
}