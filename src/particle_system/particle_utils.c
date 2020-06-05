/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** particles utils
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include "particles.h"

void set(sfUint8 *pixel, sfUint8 red, sfUint8 green, sfUint8 blue)
{
    if (!pixel)
        return;
    pixel[R] = red;
    pixel[G] = green;
    pixel[B] = blue;
    pixel[A] = 255;
}

void copy(sfUint8 *from, sfUint8 *to)
{
    to[R] = from[R];
    to[G] = from[G];
    to[B] = from[B];
    to[A] = from[A];
}

void destroy_px_content(px_particle_t *effect)
{
    free(effect->buffer);
    sfTexture_destroy(effect->texture);
    sfSprite_destroy(effect->sprite);
    free(effect);
}

void destroy_px_particle(px_particle_t **effects)
{
    px_particle_t *temp = *effects;
    px_particle_t *prev;

    if (temp != NULL && temp->lifetime > 4000) {
        *effects = temp->next;
        destroy_px_content(temp);
        return;
    }
    while (temp != NULL && temp->lifetime <= 4000) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL)
        return;
    prev->next = temp->next;
    destroy_px_content(temp);
    return;
}