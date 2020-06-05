/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** player animation
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include "maps.h"
#include "player.h"
#include "my.h"

int choose_event(states_t *boy, states_t *girl, sfRenderWindow *window,
sfEvent *event)
{
    while (sfRenderWindow_pollEvent(window, event)) {
        if (event->type == sfEvtClosed) {
            sfRenderWindow_close(window);
            return (3);
        } else if (event->type == sfEvtMouseButtonPressed && event->mouseButton.button == sfMouseLeft) {
            if (is_sprite_clicked(boy->sprite, window) == 1)
                return (1);
            else if (is_sprite_clicked(girl->sprite, window) == 1)
                return (2);
        }
    }
    return (0);
}

void display_choose_player(sfRenderWindow *window, choose_player_t *menu,
sfView *main_view)
{
    sfRenderWindow_setView(window, main_view);
    sfRenderWindow_drawSprite(window, menu->backgrond, NULL);
    sfRenderWindow_drawSprite(window, menu->boy->img->sprite, NULL);
    sfRenderWindow_drawSprite(window, menu->girl->img->sprite, NULL);
    sfRenderWindow_drawText(window, menu->text, NULL);
    sfRenderWindow_display(window);
}

choose_player_t *init_choose_menu(char *name, sfFont *font)
{
    choose_player_t *menu = malloc(sizeof(choose_player_t));
    sfVector2f pos = set_vector(850, 400);
    sfVector2f pos_bg = set_vector(580, 130);
    sfVector2f scale = set_vector(1.5, 1.5);

    menu->text = create_text("Click to choose your player :", 690, 230, font);
    menu->boy = init_player("src/media/player1", name);
    menu->girl = init_player("src/media/player2", name);
    sfSprite_setPosition(menu->boy->img->sprite, pos);
    pos.x = 1080;
    sfSprite_setPosition(menu->girl->img->sprite, pos);
    menu->texture = sfTexture_createFromFile("src/media/background.png", NULL);
    menu->backgrond = sfSprite_create();
    sfSprite_setTexture(menu->backgrond, menu->texture, sfTrue);
    sfSprite_setScale(menu->backgrond, scale);
    sfSprite_setPosition(menu->backgrond, pos_bg);
    return (menu);
}

void destroy_choose_menu(choose_player_t *menu)
{
    sfText_destroy(menu->text);
    sfTexture_destroy(menu->texture);
    sfSprite_destroy(menu->backgrond);
    free(menu);
}

player_t *choose_player(sfRenderWindow *window, sfEvent *event, char *name,
game_t *game)
{
    choose_player_t *menu = init_choose_menu(name, game->dialog->font);
    player_t *choosen = NULL;
    int state = 0;

    while (state == 0 && sfRenderWindow_isOpen(window)) {
        sfRenderWindow_clear(window, sfBlack);
        display_elements(game->map, window, game);
        display_choose_player(window, menu, game->main_view);
        state = choose_event(menu->boy->img, menu->girl->img, window, event);
    }
    if (state == 1) {
        destroy_player(menu->girl);
        choosen = menu->boy;
    } else if (state == 2) {
        destroy_player(menu->boy);
        choosen = menu->girl;
    }
    destroy_choose_menu(menu);
    return (choosen);
}