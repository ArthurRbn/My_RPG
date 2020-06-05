/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** init particles
*/

#include <SFML/Graphics.h>
#include <math.h>
#include <stdlib.h>
#include "my.h"
#include "particles.h"
#include "game.h"

void set_angle(particle_t *particle, int dir)
{
    int adjacent = 10 + (rand() % 30);
    int oppose = 10 + (rand() % 30);
    float hyoptenuse = 0;
    float radian = 0;

    if (oppose > adjacent) {
        radian = oppose / adjacent;
        radian = atanf(radian);
    } else if (oppose < adjacent) {
        hyoptenuse = hypot(adjacent, oppose);
        radian = acosf(adjacent / hyoptenuse);
    }
    particle->radian = radian;
    particle->dir = dir;
    if (radian == 0)
        set_angle(particle, dir);
}

particle_t *add_node(const sfTexture *img, particle_t *next, int dir,
sfVector2f pos)
{
    particle_t *new_node = malloc(sizeof(particle_t));
    sfIntRect rect;

    if (!new_node)
        return (NULL);
    new_node->texture = sfTexture_copy(img);
    new_node->particle = sfSprite_create();
    sfSprite_setTexture(new_node->particle, new_node->texture, sfTrue);
    rect = sfSprite_getTextureRect(new_node->particle);
    sfSprite_setOrigin(new_node->particle, set_vector(rect.width / 2, rect.height / 2));
    sfSprite_setScale(new_node->particle, set_vector(0.1f, 0.1f));
    pos.x -= 3;
    pos.y += 5;
    sfSprite_setPosition(new_node->particle, pos);
    new_node->time = 0;
    new_node->refresh = 0;
    new_node->next = next;
    set_angle(new_node, dir);
    return (new_node);
}

void create_particles(game_t *game, const sfTexture *img,
sfVector2f player_pos)
{
    int dir = 0;
    int nb = 0;
    particle_t *list = game->particles;

    while (dir < 4) {
        while (nb < 2) {
            list = add_node(img, list, dir, player_pos);
            ++nb;
        }
        nb = 0;
        ++dir;
    }
    game->particles = list;
}

void add_particle(game_t *game)
{
    sfVector2f player_pos = sfSprite_getPosition(game->player->img->sprite);
    const sfTexture *img;

    img = sfTexture_createFromFile("src/media/tileDirt.png", NULL);
    create_particles(game, img, player_pos);
}