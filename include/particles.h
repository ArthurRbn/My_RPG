/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** particle system
*/

#ifndef PARTICLES_H_
#define PARTICLES_H_

#include <SFML/Graphics.h>
#include <SFML/Config.h>

#define SPEED 5;
#define R 0
#define G 1
#define B 2
#define A 3

typedef struct px_particle_s
{
    sfSprite *sprite;
    sfTexture *texture;
    sfUint8 *buffer;
    int width;
    int height;
    int r;
    int g;
    int b;
    float refresh;
    float lifetime;
    sfSprite *reference;
    struct px_particle_s *next;
} px_particle_t;

typedef struct particle_s
{
    sfTexture *texture;
    sfSprite *particle;
    float time;
    float refresh;
    float radian;
    int dir;
    struct particle_s *next;
} particle_t;

void reset(sfUint8 *pixel);
void set(sfUint8 *pixel, sfUint8 red, sfUint8 green, sfUint8 blue);
void copy(sfUint8 *from, sfUint8 *to);

#endif /* !PARTICLES_H_ */