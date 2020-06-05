/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** move player
*/

#include "my.h"
#include "maps.h"
#include "player.h"
#include "game.h"

int move_rect(game_t *game)
{
    sfIntRect rect = sfSprite_getTextureRect(game->player->img->sprite);

    if (game->player->refresh > 5) {
        rect.left += 16;
        if (rect.left > 89)
            rect.left = 0;
        sfSprite_setTextureRect(game->player->img->sprite, rect);
        game->player->refresh = 0;
        add_particle(game);
        return (1);
    }
    if (game->player->refresh > 2)
        return (1);
    return (0);
}

int analyse_colision(sfSprite *player, block_t *obj)
{
    sfFloatRect player_rect;
    sfFloatRect obj_rect;
    sfBool colision = sfFalse;
    int ret = 4;

    if (obj->sprite == NULL || obj->id > 8)
        return (4);
    player_rect = sfSprite_getGlobalBounds(player);
    obj_rect = sfSprite_getGlobalBounds(obj->sprite);
    colision = sfFloatRect_intersects(&obj_rect, &player_rect, NULL);
    if (colision == sfTrue)
        ret = get_blocked_direction(player, obj->sprite, obj->id);
    return (ret);
}

int check_colision(sfSprite *player, block_t ***obj)
{
    int blocked_dir = 4;

    for (int i = 0; obj[i] != NULL && blocked_dir == 4; ++i) {
        for (int j = 0; obj[i][j] != NULL && blocked_dir == 4; ++j) {
            blocked_dir = analyse_colision(player, obj[i][j]);
        }
    }
    return (blocked_dir);
}

void avoid_sprite_bug(game_t *game, int dir)
{
    sfVector2f pos = sfSprite_getPosition(game->player->img->sprite);
    sfIntRect rect = sfSprite_getTextureRect(game->player->img->sprite);
    states_t *temp = game->player->states;

    if (dir != game->player->img->dir) {
        rect.left = 0;
        sfSprite_setTextureRect(game->player->img->sprite, rect);
    }
    game->player->img->sprite = game->player->img->calm;
    while (temp && temp->dir != dir)
        temp = temp->next;
    game->player->img = temp;
    sfSprite_setPosition(game->player->img->sprite, pos);
}

void move_player(game_t *game, int dir)
{
    int blocked_dir = check_colision(game->player->img->sprite, game->map->obj);

    if (stay_in_map(game->map, dir, game->player) == 1)
        return;
    avoid_sprite_bug(game, dir);
    if (move_rect(game) == 0)
        return;
    if (dir == 0 && blocked_dir != 1 && blocked_dir != 2)
        sfSprite_move(game->player->img->sprite, set_vector(8, 0));
    else if (dir == 1 && blocked_dir != 2 && blocked_dir != 3)
        sfSprite_move(game->player->img->sprite, set_vector(0, 8));
    if (dir == 2 && blocked_dir != 0 && blocked_dir != 3)
        sfSprite_move(game->player->img->sprite, set_vector(-8, 0));
    else if (dir == 3 && blocked_dir != 0 && blocked_dir != 1)
        sfSprite_move(game->player->img->sprite, set_vector(0, -8));
}