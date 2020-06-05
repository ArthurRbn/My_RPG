/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** animation enemies
*/

#include <SFML/Graphics.h>
#include "my.h"
#include "game.h"

void move_enemy_rect(enemy_t *enemy)
{
    sfIntRect rect = sfSprite_getTextureRect(enemy->img->sprite);

    enemy->refresh = 0;
    rect.left += 16;
    if (rect.left > 89)
        rect.left = 0;
    sfSprite_setTextureRect(enemy->img->sprite, rect);
}

void translation(int dir, int x, int y, enemy_t *enemy)
{
    states_enemy_t *temp = enemy->states;
    sfVector2f pos = sfSprite_getPosition(enemy->img->sprite);

    while (temp && temp->dir != dir)
        temp = temp->next;
    if (temp != NULL) {
        enemy->img = temp;
        sfSprite_setPosition(enemy->img->sprite, pos);
    }
    sfSprite_move(enemy->img->sprite, (sfVector2f){x, y});
}

void move_enemy(sfSprite *player, enemy_t *enemy, block_t ***obj)
{
    sfVector2f player_pos = sfSprite_getPosition(player);
    sfVector2f enemy_pos = sfSprite_getPosition(enemy->img->sprite);
    int delta_x = player_pos.x - enemy_pos.x;
    int delta_y = player_pos.y - enemy_pos.y;
    int blocked = check_colision(enemy->img->sprite, obj);

    if (delta_x < 0 && blocked != 0 && blocked != 3) {
        translation(2, -5, 0, enemy);
        return;
    } else if (delta_x > 0 && delta_x > 5 && blocked != 1 && blocked != 2) {
        translation(0, 5, 0, enemy);
        return;
    } if (delta_y > 0 && delta_y > 5 && blocked != 2 && blocked != 3) {
        translation(1, 0, 5, enemy);
        return;
    } else if (delta_y < 0 && delta_y < -5 && blocked != 0 && blocked != 1) {
        translation(3, 0, -5, enemy);
        return;
    }
}

void killed_enemies_effect(game_t *game)
{
    sfIntRect rect;
    sfFloatRect pos;
    int rgb[3] = {236, 56, 45};

    for (enemy_t *temp = game->enemies; temp != NULL; temp = temp->next) {
        if (temp->hp <= 0 && temp->alive == TRUE) {
            actualize_quests(game->quests, 0, NULL, game->player);
            rect = sfSprite_getTextureRect(temp->img->sprite);
            game->effects = init_px_particles(game->effects, rgb, rect.width, rect.height);
            if (game->effects != NULL) {
                game->effects->reference = NULL;
                pos = sfSprite_getGlobalBounds(temp->img->sprite);
                sfSprite_setPosition(game->effects->sprite,
                set_vector(pos.left, pos.top));
                sfSprite_setScale(game->effects->sprite, (sfVector2f){2, 2});
            }
        }
    }
}

void refresh_enemies(game_t *game)
{
    sfFloatRect p = sfSprite_getGlobalBounds(game->player->img->sprite);
    sfFloatRect r;

    killed_enemies_effect(game);
    handle_respawn(game->enemies);
    for (enemy_t *temp = game->enemies; temp != NULL; temp = temp->next) {
        if (get_distance(game->player->img->sprite, temp->img->sprite) < 200 && temp->refresh > 5 && temp->alive == TRUE) {
            move_enemy(game->player->img->sprite, temp, game->map->obj);
            move_enemy_rect(temp);
        } else if (temp->refresh > 5 && temp->alive == TRUE) {
            enemy_standby(temp, game->map->obj);
            move_enemy_rect(temp);
        }
        r = sfSprite_getGlobalBounds(temp->img->sprite);
        if (sfFloatRect_intersects(&p, &r, &(sfFloatRect){0, 0, 30, 30}) == 1 && temp->alive == TRUE)
            enemy_attack(temp, game->player);
    }
}