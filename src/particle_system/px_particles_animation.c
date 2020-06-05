/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** pixel particles
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include <stdbool.h>
#include "my.h"
#include "game.h"
#include "particles.h"

void draw_effects(sfRenderWindow *win, px_particle_t *effect)
{
    px_particle_t *temp = effect;
    sfFloatRect pos = {10, 10, 10, 10};

    while (temp) {
        if (!temp->texture || !temp->sprite)
            return;
        if (temp->reference != NULL) {
            pos = sfSprite_getGlobalBounds(temp->reference);
            sfSprite_setPosition(temp->sprite, set_vector(pos.left + 2, pos.top + 5));
        }
        sfTexture_updateFromPixels(temp->texture, temp->buffer, temp->width, temp->height, 0, 0);
        sfSprite_setTexture(temp->sprite, temp->texture, sfTrue);
        sfRenderWindow_drawSprite(win, temp->sprite, NULL);
        temp = temp->next;
    }
}

bool check(sfUint8 *pixel, sfUint8 red, sfUint8 green, sfUint8 blue)
{
    return (pixel[R] == red && pixel[G] == green && pixel[B] == blue);
}

void refresh_pixel(sfUint8 *buffer, int i, int width)
{
    buffer[i + A] -= 1;
    if (i > width * 4 && buffer[i + A] > 30)
        copy(&buffer[i], &buffer[i - width * 4]);
    reset(&buffer[i]);
}

void update_px_particles(int width, int height, px_particle_t *rgb)
{
    int buffer_size = width * height * 4;

    set(&rgb->buffer[buffer_size - rand() % width * 4], rgb->r, rgb->g, rgb->b);
    set(&rgb->buffer[buffer_size - rand() % width * 4], rgb->r, rgb->g, rgb->b);
    set(&rgb->buffer[buffer_size - rand() % width * 4], rgb->r, rgb->g, rgb->b);
    set(&rgb->buffer[buffer_size - rand() % width * 4], rgb->r, rgb->g, rgb->b);
    for (int i = 0; i < width * height * 4; i += 4) {
        if (check(&rgb->buffer[i], rgb->r, rgb->g, rgb->b)) {
            refresh_pixel(rgb->buffer, i, width);
        }
    }
}