/*
** EPITECH PROJECT, 2020
** parallax
** File description:
** parallax
*/

#ifndef para
#define para

#include <SFML/Graphics.h>
#include "button.h"
#include "inventory.h"

#define STAT_FIELDS 4

typedef struct parallax_s
{
    sfSprite *sprite;
    sfTexture *texture;
} parallax_t;

typedef struct stat_menu_s
{
    sfTexture *t_invent;
    sfSprite *inventory;
    sfTexture *t_bg;
    sfSprite *background;
    sfText **quests;
    sfText **stats;
    inventory_t **items;
    sfVector2f pos;
    button_t *exit;
} stat_menu_t;

typedef struct main_menu_s
{
    parallax_t **bg;
    button_t *play;
    button_t *how_to;
    button_t *quit;
} main_menu_t;

typedef struct pause_menu_s
{
    button_t *resume;
    button_t *quit;
    button_t *main_menu;
    button_t *settings;
    sfTexture *texture;
    sfSprite *bg;
} pause_menu_t;

typedef struct options_menu_s
{
    sfText *sound;
    button_t *plus_sound;
    button_t *minus_sound;
    sfText *vol_sound;
    sfText *music;
    button_t *plus_music;
    button_t *minus_music;
    sfText *vol_music;
    button_t *stop_sound;
    button_t *stop_music;
    button_t *exit;
    sfTexture *texture;
    sfSprite *bg;
} options_menu_t;

typedef struct how_to_play_s
{
    sfSprite *sprite;
    sfTexture *texture;
    button_t *button;
} how_to_play_t;

typedef struct menus_s
{
    options_menu_t *settings;
    pause_menu_t *pause;
    main_menu_t *start;
    stat_menu_t *stats;
    how_to_play_t *how_to;
} menus_t;

main_menu_t *init_main_menu(void);
pause_menu_t *init_pause_menu(void);
options_menu_t *init_settings_menu(void);
stat_menu_t *init_stat_menu(void);
how_to_play_t *init_how_to(void);
void set_settings_pos(options_menu_t *settings, sfRenderWindow *window,
sfView *view);
void init_settings_texts(options_menu_t *menu, sfFont *font);
void set_pause_positions(pause_menu_t *pause, sfRenderWindow *window,
sfView *view);
void destroy_main_menu(main_menu_t *menu);
void destroy_pause_menu(pause_menu_t *menu);
void destroy_settings_menu(options_menu_t *menu);
void destroy_stat_menu(stat_menu_t *menu);
void destroy_how_to(how_to_play_t *menu);

#endif /* !para */