/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** initialize game
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include <time.h>
#include "my.h"
#include "quests.h"

sfRenderWindow *init_window(void)
{
    sfRenderWindow *window;
    sfVideoMode v_mode;

    v_mode.bitsPerPixel = 24;
    v_mode.height = 1080;
    v_mode.width = 1920;
    window = sfRenderWindow_create(v_mode, "My_RPG", sfDefaultStyle, NULL);
    if (!window)
        return (NULL);
    sfRenderWindow_setFramerateLimit(window, 40);
    sfRenderWindow_setKeyRepeatEnabled(window, sfTrue);
    return (window);
}

static void get_all_elements(game_t *game, sfRenderWindow *window)
{
    game->map = init_map("src/media/map1");
    game->clock = sfClock_create();
    create_views(game, window);
    game->particles = NULL;
    game->effects = NULL;
    game->player = NULL;
    game->npc = init_all_npc();
    game->dialog = init_dialog();
    game->enemies = init_enemies();
    game->quests = get_quests();
    game->sounds = get_sounds();
    game->ui = init_ui();
    game->menus = get_menus();
    if (game->menus != NULL && game->dialog != NULL)
        init_settings_texts(game->menus->settings, game->dialog->font);
}

game_t *init_game(sfRenderWindow *window, sfEvent *event, char *name)
{
    game_t *game = malloc(sizeof(game_t));

    if (!game)
        return (NULL);
    srand(time(NULL));
    get_all_elements(game, window);
    game->display = MAIN_MENU;
    if (!game->map || !game->npc || !game->enemies || !game->quests || !game->sounds || !game->menus || !game->ui || !game->minimap || !game->clock || !game->dialog || !game->main_view)
        return (NULL);
    game->player = choose_player(window, event, name, game);
    if (!game->player)
        return (NULL);
    else
        return (game);
}