/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** init settings menu
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include "my.h"
#include "game.h"
#include "button.h"
#include "menus.h"

void set_settings_positions3(options_menu_t *settings, sfRenderWindow *window,
sfView *view)
{
    sfVector2i relative;
    sfVector2f pos;

    pos = sfText_getPosition(settings->vol_music);
    pos.x -= 100;
    pos.y -= 60;
    sfText_setPosition(settings->music, pos);
    pos = sfText_getPosition(settings->vol_sound);
    pos.x -= 100;
    pos.y -= 60;
    sfText_setPosition(settings->sound, pos);
    relative.x = 0;
    relative.y = 0;
    pos = sfRenderWindow_mapPixelToCoords(window, relative, view);
    sfSprite_setPosition(settings->bg, pos);
}

void set_settings_positions2(options_menu_t *settings, sfRenderWindow *window,
sfView *view)
{
    sfVector2i relative;
    sfVector2f pos;

    relative.x = settings->plus_sound->pos.x;
    relative.y = settings->plus_sound->pos.y;
    pos = sfRenderWindow_mapPixelToCoords(window, relative, view);
    sfSprite_setPosition(settings->plus_sound->sprite, pos);
    pos.x -= 65;
    sfText_setPosition(settings->vol_sound, pos);
    relative.x = settings->plus_music->pos.x;
    relative.y = settings->plus_music->pos.y;
    pos = sfRenderWindow_mapPixelToCoords(window, relative, view);
    sfSprite_setPosition(settings->plus_music->sprite, pos);
    pos.x -= 65;
    sfText_setPosition(settings->vol_music, pos);
    relative.x = settings->stop_sound->pos.x;
    relative.y = settings->stop_sound->pos.y;
    pos = sfRenderWindow_mapPixelToCoords(window, relative, view);
    sfSprite_setPosition(settings->stop_sound->sprite, pos);
    set_settings_positions3(settings, window, view);
}

void set_settings_pos(options_menu_t *settings, sfRenderWindow *window,
sfView *view)
{
    sfVector2i relative;
    sfVector2f pos;

    relative.x = settings->exit->pos.x;
    relative.y = settings->exit->pos.y;
    pos = sfRenderWindow_mapPixelToCoords(window, relative, view);
    sfSprite_setPosition(settings->exit->sprite, pos);
    relative.x = settings->minus_music->pos.x;
    relative.y = settings->minus_music->pos.y;
    pos = sfRenderWindow_mapPixelToCoords(window, relative, view);
    sfSprite_setPosition(settings->minus_music->sprite, pos);
    relative.x = settings->minus_sound->pos.x;
    relative.y = settings->minus_sound->pos.y;
    pos = sfRenderWindow_mapPixelToCoords(window, relative, view);
    sfSprite_setPosition(settings->minus_sound->sprite, pos);
    relative.x = settings->stop_music->pos.x;
    relative.y = settings->stop_music->pos.y;
    pos = sfRenderWindow_mapPixelToCoords(window, relative, view);
    sfSprite_setPosition(settings->stop_music->sprite, pos);
    set_settings_positions2(settings, window, view);
}

void init_settings_texts(options_menu_t *menu, sfFont *font)
{
    menu->music = create_text("Music Volume :", 840, 220, font);
    menu->sound = create_text("Sounds Volume :", 820, 400, font);
    menu->vol_music = create_text("100", 750, 300, font);
    menu->vol_sound = create_text("100", 750, 500, font);
    menu->texture = sfTexture_createFromFile("src/media/fond_gris.jpg", NULL);
    menu->bg = sfSprite_create();
    sfSprite_setTexture(menu->bg, menu->texture, sfTrue);
    sfSprite_setColor(menu->bg, (sfColor){192, 192, 192, 200});
}

options_menu_t *init_settings_menu(void)
{
    options_menu_t *menu = malloc(sizeof(options_menu_t));

    if (!menu)
        return (NULL);
    menu->vol_music = NULL;
    menu->vol_sound = NULL;
    menu->minus_music = init_button("src/media/minus.png", (sfVector2f){860, 300}, (sfIntRect){0, 0, 60, 58});
    menu->minus_sound = init_button("src/media/minus.png", (sfVector2f){860, 470}, (sfIntRect){0, 0, 60, 58});
    menu->plus_music = init_button("src/media/plus.png", (sfVector2f){1010, 300}, (sfIntRect){0, 0, 60, 58});
    menu->plus_sound = init_button("src/media/plus.png", (sfVector2f){1010, 470}, (sfIntRect){0, 0, 60, 58});
    menu->stop_music = init_button("src/media/mute.png", (sfVector2f){1110, 300}, (sfIntRect){0, 0, 128, 75});
    menu->stop_sound = init_button("src/media/mute.png", (sfVector2f){1110, 470}, (sfIntRect){0, 0, 128, 75});
    menu->exit = init_button("src/media/exit.png", (sfVector2f){1500, 800},(sfIntRect){0, 0, 160, 75});
    return (menu);
}