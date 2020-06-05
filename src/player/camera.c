/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** camera
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include "player.h"
#include "game.h"
#include "my.h"

void manage_view(game_t *game, sfRenderWindow *window)
{
    sfVector2f player_pos = sfSprite_getPosition(game->player->img->sprite);
    sfVector2f absolute_pos;

    sfView_setCenter(game->main_view, player_pos);
    sfView_setCenter(game->minimap->view, player_pos);
    absolute_pos = sfRenderWindow_mapPixelToCoords(window, (sfVector2i){1585, 15}, game->main_view);
    sfSprite_setPosition(game->minimap->sprite, absolute_pos);
    sfRenderWindow_setView(window, game->main_view);
}

minimap_t *init_minimap(sfVector2u size)
{
    sfFloatRect rect = {0.834, 0.04, 0.15, 0.19};
    minimap_t *map = malloc(sizeof(minimap_t));

    map->view = sfView_create();
    sfView_setViewport(map->view, rect);
    sfView_zoom(map->view, 2.5);
    sfView_setCenter(map->view, set_vector(size.x / 2, size.y / 2));
    map->texture = sfTexture_createFromFile("src/media/minimap_box.png", NULL);
    map->sprite = sfSprite_create();
    sfSprite_setTexture(map->sprite, map->texture, sfTrue);
    sfSprite_setScale(map->sprite, set_vector(1, 3));
    sfSprite_setPosition(map->sprite, set_vector(500, 20));
    return (map);
}

void create_views(game_t *game, sfRenderWindow *window)
{
    sfFloatRect rect;
    sfVector2u size = sfRenderWindow_getSize(window);

    rect.top = 0;
    rect.left = 0;
    rect.width = 1;
    rect.height = 1;
    game->main_view = sfView_create();
    sfView_setViewport(game->main_view, rect);
    sfView_setSize(game->main_view, set_vector(size.x, size.y));
    sfView_setCenter(game->main_view, set_vector(size.x / 2, size.y / 2));
    sfView_zoom(game->main_view, 1);
    game->minimap = init_minimap(size);
}

int stay_in_map(map_t *map, int dir, player_t *player)
{
    sfVector2f pos = sfSprite_getPosition(player->img->sprite);

    if (dir == 0 && (map->borders.width - pos.x) > 30)
        return (0);
    else if (dir == 1 && (map->borders.height - pos.y) > 50)
        return (0);
    if (dir == 2 && pos.x > 30)
        return (0);
    else if (dir == 3 && pos.y > 30)
        return (0);
    return (1);
}