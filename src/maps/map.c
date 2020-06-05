/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** maps
*/

#include <SFML/Graphics.h>
#include "maps.h"
#include "game.h"
#include "my.h"

void check_layer(sfRenderWindow *window, block_t *obj, sfSprite *player)
{
    sfFloatRect r1 = sfSprite_getGlobalBounds(player);
    sfFloatRect r2;
    sfBool state = sfFalse;

    if (obj->id != -16 || obj->id > 8) {
        sfRenderWindow_drawSprite(window, obj->sprite, NULL);
        r2 = sfSprite_getGlobalBounds(obj->sprite);
        state = sfFloatRect_intersects(&r1, &r2, NULL);
        if (state == sfTrue && (r1.top + r1.height + 10) > (r2.top + r2.height))
            sfRenderWindow_drawSprite(window, player, NULL);
    }
}

void display_obj(block_t ***obj, sfRenderWindow *window, sfSprite *player)
{
    for (int i = 0; obj[i] != NULL; ++i)
        for (int j = 0; obj[i][j] != NULL; ++j)
            check_layer(window, obj[i][j], player);
}

void display_elements(map_t *map, sfRenderWindow *window, game_t *game)
{
    sfRenderWindow_drawSprite(window, map->map, NULL);
    if (game->player != NULL) {
        display_particles(game, window);
        sfRenderWindow_drawSprite(window, game->player->img->sprite, NULL);
        display_npc(game->npc, window, game->player->img->sprite);
        display_enemies(game->enemies, window, game->player->img->sprite);
        draw_effects(window, game->effects);
        display_obj(game->map->obj, window, game->player->img->sprite);
    }
}