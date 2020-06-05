/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** player attack animation
*/

#include <SFML/Graphics.h>
#include "game.h"
#include "player.h"
#include "enemy.h"
#include "my.h"

void set_sprites_positions(player_t *player, enemy_t *enemy)
{
    sfVector2f pos_player = sfSprite_getPosition(player->img->sprite);
    sfVector2f pos_enemy;
    states_t *temp = player->states;
    enemy_t *temp_enemy = enemy;
    states_enemy_t *temp2;

    while (temp) {
        sfSprite_setPosition(temp->calm, pos_player);
        sfSprite_setPosition(temp->fight, pos_player);
        temp = temp->next;
    }
    while (temp_enemy) {
        temp2 = temp_enemy->states;
        pos_enemy = sfSprite_getPosition(temp_enemy->img->sprite);
        while (temp2) {
            sfSprite_setPosition(temp2->sprite, pos_enemy);
            temp2 = temp2->next;
        }
        temp_enemy = temp_enemy->next;
    }
}

void refresh_player_stats(game_t *game)
{
    player_t *player = game->player;
    sfIntRect rect;
    int rgb[3] = {10, 237, 138};

    if (player->stats->xp >= player->stats->lvl * 35) {
        player->stats->xp -= player->stats->lvl * 35;
        player->stats->lvl += 1;
        player->stats->damage += 10;
        player->stats->max_hp += 10;
        player->stats->hp = player->stats->max_hp;
        rect = sfSprite_getTextureRect(player->img->sprite);
        game->effects = init_px_particles(game->effects, rgb, rect.width, rect.height);
        if (game->effects != NULL)
            game->effects->reference = game->player->img->sprite;
        sfSprite_setScale(game->effects->sprite, (sfVector2f){2.5, 2.8});
        sfSound_play(game->sounds->lvl_up);
    }
}

void check_attack_touch(player_t *player, enemy_t *enemy)
{
    enemy_t *temp = enemy;
    sfFloatRect rect1 = sfSprite_getGlobalBounds(player->img->sprite);
    sfFloatRect rect2;

    while (temp) {
        rect2 = sfSprite_getGlobalBounds(temp->img->sprite);
        if (sfFloatRect_intersects(&rect1, &rect2, NULL) == sfTrue && temp->alive == TRUE)
            temp->hp -= player->stats->damage;
        if (temp->hp <= 0 && temp->alive == TRUE)
            player->stats->xp += 10;
        temp = temp->next;
    }
}

void refresh_player(player_t *player, enemy_t *enemy, game_t *game)
{
    sfIntRect rect;
    sfVector2f pos;

    if (!player)
        return;
    if (player->refresh > 20 && player->img->attack == 1) {
        rect = sfSprite_getTextureRect(player->img->fight);
        rect.left += rect.width;
        if (rect.left > 130) {
            check_attack_touch(player, enemy);
            pos = sfSprite_getPosition(player->img->sprite);
            rect.left = 0;
            player->img->attack = 0;
            sfSprite_setTextureRect(player->img->fight, rect);
            player->img->sprite = player->img->calm;
            sfSprite_setPosition(player->img->sprite, pos);
        }
        sfSprite_setTextureRect(player->img->fight, rect);
    }
    refresh_player_stats(game);
}

void set_attack(game_t *game)
{
    sfVector2f pos;

    if (game->player->attack_time > 100) {
        sfSound_play(game->sounds->attack);
        pos = sfSprite_getPosition(game->player->img->sprite);
        game->player->img->attack = 1;
        game->player->img->sprite = game->player->img->fight;
        sfSprite_setPosition(game->player->img->sprite, pos);
        game->player->attack_time = 0;
    }
}