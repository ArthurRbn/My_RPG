/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** settings menu
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include <math.h>
#include "my.h"
#include "game.h"
#include "button.h"
#include "menus.h"

void display_settings(options_menu_t *menu, sfRenderWindow *win, game_t *game)
{
    sfRenderWindow_clear(win, sfBlack);
    display_elements(game->map, win, game);
    sfRenderWindow_drawSprite(win, menu->bg, NULL);
    sfRenderWindow_drawSprite(win, menu->minus_music->sprite, NULL);
    sfRenderWindow_drawSprite(win, menu->minus_sound->sprite, NULL);
    sfRenderWindow_drawSprite(win, menu->plus_music->sprite, NULL);
    sfRenderWindow_drawSprite(win, menu->plus_sound->sprite, NULL);
    sfRenderWindow_drawSprite(win, menu->stop_music->sprite, NULL);
    sfRenderWindow_drawSprite(win, menu->stop_sound->sprite, NULL);
    sfRenderWindow_drawSprite(win, menu->exit->sprite, NULL);
    sfRenderWindow_drawText(win, menu->vol_music, NULL);
    sfRenderWindow_drawText(win, menu->vol_sound, NULL);
    sfRenderWindow_drawText(win, menu->music, NULL);
    sfRenderWindow_drawText(win, menu->sound, NULL);
    sfRenderWindow_display(win);
}

int settings_event(game_t *game, sfEvent *event, sfRenderWindow *window)
{
    while (sfRenderWindow_pollEvent(window, event)) {
        if (event->type == sfEvtClosed) {
            sfRenderWindow_close(window);
            return (3);
        }
        if (event->type == sfEvtMouseButtonPressed &&
        event->mouseButton.button == sfMouseLeft) {
            clicked_check(game->menus->settings->minus_music, window);
            clicked_check(game->menus->settings->minus_sound, window);
            clicked_check(game->menus->settings->plus_music, window);
            clicked_check(game->menus->settings->plus_sound, window);
            clicked_check(game->menus->settings->stop_music, window);
            clicked_check(game->menus->settings->stop_sound, window);
            clicked_check(game->menus->settings->exit, window);
            return (0);
        }
    }
    return (0);
}

void set_vol_music(sounds_t *sounds, float offset, options_menu_t *menu,
sfFont *font)
{
    float volume = sfMusic_getVolume(sounds->soundtrack1);
    sfVector2f pos;

    volume = roundf(volume);
    volume += offset;
    if (offset == 0)
        volume = 0;
    if (volume >= 0 && volume <= 100) {
        sfMusic_setVolume(sounds->soundtrack1, volume);
        sfMusic_setVolume(sounds->soundtrack2, volume);
        pos = sfText_getPosition(menu->vol_music);
        menu->vol_music = create_text(nbr_str(volume), pos.x, pos.y, font);
    }
}

void set_vol_sound(sounds_t *sounds, int offset, options_menu_t *menu,
sfFont *font)
{
    float volume = sfSound_getVolume(sounds->attack);
    sfVector2f pos;

    volume = roundf(volume);
    volume += offset;
    if (offset == 0)
        volume = 0;
    if (volume >= 0 && volume <= 100) {
        sfSound_setVolume(sounds->attack, volume);
        sfSound_setVolume(sounds->bye, volume);
        sfSound_setVolume(sounds->hello, volume);
        sfSound_setVolume(sounds->lvl_up, volume);
        sfSound_setVolume(sounds->item, volume);
        pos = sfText_getPosition(menu->vol_sound);
        menu->vol_sound = create_text(nbr_str(volume), pos.x, pos.y, font);
    }
}

void settings_menu(game_t *g, sfRenderWindow *window, sfEvent *event)
{
    set_settings_pos(g->menus->settings, window, g->main_view);
    while (g->display == SETTINGS && sfRenderWindow_isOpen(window)) {
        display_settings(g->menus->settings, window, g);
        settings_event(g, event, window);
        if (hover_check(g->menus->settings->minus_music, window, event) == 1)
            set_vol_music(g->sounds, -10, g->menus->settings, g->dialog->font);
        if (hover_check(g->menus->settings->minus_sound, window, event) == 1)
            set_vol_sound(g->sounds, -10, g->menus->settings, g->dialog->font);
        if (hover_check(g->menus->settings->plus_music, window, event) == 1)
            set_vol_music(g->sounds, +10, g->menus->settings, g->dialog->font);
        if (hover_check(g->menus->settings->plus_sound, window, event) == 1)
            set_vol_sound(g->sounds, +10, g->menus->settings, g->dialog->font);
        if (hover_check(g->menus->settings->stop_music, window, event) == 1)
            set_vol_music(g->sounds, 0, g->menus->settings, g->dialog->font);
        if (hover_check(g->menus->settings->stop_sound, window, event) == 1)
            set_vol_sound(g->sounds, 0, g->menus->settings, g->dialog->font);
        if (hover_check(g->menus->settings->exit, window, event) == 1)
            g->display = PAUSE_MENU;
    }
}