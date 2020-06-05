/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** init pixel particles
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"
#include "particles.h"

void reset(sfUint8 *pixel)
{
    pixel[R] = 0;
    pixel[G] = 0;
    pixel[B] = 0;
    pixel[A] = 0;
}

px_particle_t *init_px_particles(px_particle_t *next, int *rgb, int width,
int height)
{
    px_particle_t *new_px = malloc(sizeof(px_particle_t));

    if (!new_px)
        return (next);
    new_px->buffer = malloc(sizeof(sfUint8 *) * (height * width * 4));
    if (!new_px->buffer)
        return (next);
    new_px->width = width;
    new_px->height = height;
    new_px->sprite = sfSprite_create();
    new_px->texture = sfTexture_create(width, height);
    sfSprite_setTexture(new_px->sprite, new_px->texture, sfTrue);
    new_px->r = rgb[0];
    new_px->g = rgb[1];
    new_px->b = rgb[2];
    new_px->refresh = 0;
    new_px->lifetime = 0;
    new_px->next = next;
    for (int i = 0; i < (height * width * 4); ++i)
        new_px->buffer[i] = 0;
    return (new_px);
}