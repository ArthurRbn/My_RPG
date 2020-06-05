/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** destroy various elements
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include "particles.h"

void destroy_particles(particle_t *particle)
{
    particle_t *prev = particle;

    while (particle) {
        prev = particle;
        particle = particle->next;
        sfTexture_destroy(prev->texture);
        sfSprite_destroy(prev->particle);
        free(prev);
    }
}

void destroy_effects(px_particle_t *effects)
{
    px_particle_t *prev = effects;

    while (effects) {
        prev = effects;
        effects = effects->next;
        sfTexture_destroy(prev->texture);
        sfSprite_destroy(prev->sprite);
        free(prev->buffer);
        free(prev);
    }
}