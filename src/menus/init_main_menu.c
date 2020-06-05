/*
** EPITECH PROJECT, 2020
** parallax
** File description:
** parallax
*/

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <SFML/Window.h>
#include <SFML/Audio.h>
#include <stdio.h>
#include "menus.h"

static void fill_bg(parallax_t **bg)
{
    sfVector2f pos = {1920, 0};

    for (int i = 0; i < 10; ++i) {
        if (i % 2 == 0)
            pos.x = 1920;
        else if (i % 2 == 1)
            pos.x = 0;
        bg[i]->sprite = sfSprite_create();
        if (!bg[i]->sprite)
            return;
        sfSprite_setTexture(bg[i]->sprite, bg[i]->texture, sfTrue);
        sfSprite_setPosition(bg[i]->sprite, pos);
    }
}

static void init_bg2(parallax_t **bg)
{
    bg[0]->texture = sfTexture_createFromFile("src/media/bg_1.png", NULL);
    bg[1]->texture = sfTexture_createFromFile("src/media/bg_1.png", NULL);
    bg[2]->texture = sfTexture_createFromFile("src/media/bg_2.png", NULL);
    bg[3]->texture = sfTexture_createFromFile("src/media/bg_2.png", NULL);
    bg[4]->texture = sfTexture_createFromFile("src/media/bg_3.png", NULL);
    bg[5]->texture = sfTexture_createFromFile("src/media/bg_3.png", NULL);
    bg[6]->texture = sfTexture_createFromFile("src/media/bg_4.png", NULL);
    bg[7]->texture = sfTexture_createFromFile("src/media/bg_4.png", NULL);
    bg[8]->texture = sfTexture_createFromFile("src/media/bg_5.png", NULL);
    bg[9]->texture = sfTexture_createFromFile("src/media/bg_5.png", NULL);
}

static parallax_t **init_bg(void)
{
    parallax_t **bg = malloc(sizeof(parallax_t *) * (10 + 1));
    int i = 0;

    if (!bg)
        return (NULL);
    for (int i = 0; i < 10; ++i) {
        bg[i] = malloc(sizeof(parallax_t));
        if (!bg[i])
            return (NULL);
    }
    bg[10] = NULL;
    init_bg2(bg);
    for (i = 0; bg[i] != NULL; ++i);
    if (i == 10) {
        fill_bg(bg);
        return (bg);
    } else
        return (NULL);
}

main_menu_t *init_main_menu(void)
{
    main_menu_t *menu = malloc(sizeof(main_menu_t));

    if (!menu)
        return (NULL);
    menu->bg = init_bg();
    menu->play = init_button("src/media/play.png", (sfVector2f){900, 200}, (sfIntRect){0, 0, 160, 75});
    menu->how_to = init_button("src/media/help.png", (sfVector2f){899, 300}, (sfIntRect){0, 0, 160, 75});
    menu->quit = init_button("src/media/quit.png", (sfVector2f){898, 400}, (sfIntRect){0, 0, 160, 75});
    if (!menu->bg || !menu->play || !menu->how_to || !menu->quit)
        return (NULL);
    else
        return (menu);
}

void destroy_main_menu(main_menu_t *menu)
{
    for (int i = 0; menu->bg[i] != NULL; ++i)
        free(menu->bg[i]);
    free(menu->bg);
    destroy_button(menu->play);
    destroy_button(menu->how_to);
    destroy_button(menu->quit);
}