/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** particle animation
*/

#include <SFML/Graphics.h>
#include <math.h>
#include <stdlib.h>
#include "my.h"
#include "game.h"
#include "particles.h"

int destroy_old_particles(particle_t **particles)
{
    particle_t *temp = *particles;
    particle_t *prev;

    if (temp != NULL && temp->time > 20) {
        *particles = temp->next;
        sfTexture_destroy(temp->texture);
        sfSprite_destroy(temp->particle);
        free(temp);
        return (1);
    }
    while (temp != NULL && temp->time <= 20) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL)
        return (0);
    prev->next = temp->next;
    sfTexture_destroy(temp->texture);
    sfSprite_destroy(temp->particle);
    free(temp);
    return (1);
}

void display_particles(game_t *game, sfRenderWindow *window)
{
    particle_t *temp = game->particles;

    while (temp) {
        sfRenderWindow_drawSprite(window, temp->particle, NULL);
        temp = temp->next;
    }
}

void apply_translation(particle_t *temp)
{
    sfVector2f translation = set_vector(0, 0);

    if (temp->dir == 1) {
        translation.x += cosf(temp->radian) * SPEED;
        translation.y += sinf(temp->radian) * SPEED;
    } else if (temp->dir == 2) {
        translation.x += cosf(temp->radian) * SPEED;
        translation.y -= sinf(temp->radian) * SPEED;
    }
    if (temp->dir == 3) {
        translation.x -= cosf(temp->radian) * SPEED;
        translation.y += sinf(temp->radian) * SPEED;
    } else if (temp->dir == 0) {
        translation.x -= cosf(temp->radian) * SPEED;
        translation.y -= sinf(temp->radian) * SPEED;
    }
    sfSprite_move(temp->particle, translation);
}

void move_particle(particle_t *particles)
{
    particle_t *temp = particles;

    while (temp) {
        if (temp->refresh > 2) {
            apply_translation(temp);
            temp->refresh = 0;
        }
        temp = temp->next;
    }
}

void refresh_all_px(game_t *game)
{
    px_particle_t *temp = game->effects;

    move_particle(game->particles);
    while (temp) {
        if (temp->refresh > 30) {
            update_px_particles(temp->width, temp->height, temp);
            sfSprite_setTexture(temp->sprite, temp->texture, sfTrue);
            temp->refresh = 0;
        }
        temp = temp->next;
    }
}