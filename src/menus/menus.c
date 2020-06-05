/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** general functions for menus
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include "game.h"
#include "button.h"
#include "menus.h"
#include "my.h"

menus_t *get_menus(void)
{
    menus_t *menus = malloc(sizeof(menus_t));

    if (!menus)
        return (NULL);
    menus->pause = init_pause_menu();
    menus->settings = init_settings_menu();
    menus->start = init_main_menu();
    menus->stats = init_stat_menu();
    menus->how_to = init_how_to();
    if (!menus->pause || !menus->settings || !menus->start || !menus->stats || !menus->how_to)
        return (NULL);
    return (menus);
}

void destroy_settings_menu(options_menu_t *menu)
{
    destroy_button(menu->exit);
    destroy_button(menu->minus_music);
    destroy_button(menu->minus_sound);
    destroy_button(menu->plus_music);
    destroy_button(menu->plus_sound);
    destroy_button(menu->stop_music);
    destroy_button(menu->stop_sound);
    sfText_destroy(menu->vol_music);
    sfText_destroy(menu->vol_sound);
    sfText_destroy(menu->music);
    sfText_destroy(menu->sound);
    sfTexture_destroy(menu->texture);
    sfSprite_destroy(menu->bg);
    free(menu);
}