/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** initialize stats, quests and inventory menu
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include "my.h"
#include "game.h"
#include "menus.h"
#include "inventory.h"

void set_inventory_pos(stat_menu_t *menu, sfRenderWindow *window, sfView *view)
{
    sfVector2f pos = sfRenderWindow_mapPixelToCoords(window,
    (sfVector2i){0, 0}, view);

    sfSprite_setPosition(menu->background, pos);
    pos.x += 200;
    pos.y += 200;
    sfSprite_setPosition(menu->inventory, pos);
    pos.x += 20;
    pos.y += 15;
    for (int i = 0; i < INV_SIZE && menu->items[i]->item != NULL; ++i) {
        sfSprite_setPosition(menu->items[i]->item->sprite, pos);
        pos.x += 50;
    }
    pos = sfRenderWindow_mapPixelToCoords(window, (sfVector2i){900, 800}, view);
    sfSprite_setPosition(menu->exit->sprite, pos);
}

static void init_stat_menu2(stat_menu_t *menu)
{
    menu->pos = (sfVector2f){200, 200};
    menu->quests = NULL;
    menu->stats = NULL;
    sfSprite_setTexture(menu->inventory, menu->t_invent, sfTrue);
    sfSprite_setTexture(menu->background, menu->t_bg, sfTrue);
    sfSprite_setPosition(menu->background, (sfVector2f){0, 0});
    sfSprite_setPosition(menu->inventory, (sfVector2f){200, 100});
    sfSprite_setScale(menu->inventory, (sfVector2f){2, 2});
    for (int i = 0; i <= INV_SIZE; ++i) {
        menu->items[i] = malloc(sizeof(inventory_t));
        if (menu->items[i] == NULL) {
            menu->items = NULL;
            return;
        }
        menu->items[i]->item = NULL;
    }
    menu->items[INV_SIZE] = NULL;
}

stat_menu_t *init_stat_menu(void)
{
    stat_menu_t *menu = malloc(sizeof(stat_menu_t));
    inventory_t **inventory = malloc(sizeof(inventory_t *) * (INV_SIZE + 1));

    if (!menu || !inventory)
        return (NULL);
    menu->items = inventory;
    menu->exit = init_button("src/media/exit.png", (sfVector2f){1500, 800}, (sfIntRect){0, 0, 160, 75});
    menu->t_bg = sfTexture_createFromFile("src/media/bg_menu.jpg", NULL);
    menu->t_invent = sfTexture_createFromFile("src/media/inventory.png", NULL);
    menu->background = sfSprite_create();
    menu->inventory = sfSprite_create();
    if (!menu->inventory || !menu->background || !menu->t_bg || !menu->t_invent || !menu->exit)
        return (NULL);
    init_stat_menu2(menu);
    if (menu->items != NULL)
        return (menu);
    return (NULL);
}