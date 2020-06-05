/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** button
*/

#ifndef BUTTON_H_
#define BUTTON_H_

#include <SFML/Graphics.h>

typedef struct button_s
{
    sfTexture *texture;
    sfSprite *sprite;
    sfVector2f pos;
    int pressed;
} button_t;

button_t *init_button(char *file, sfVector2f pos, sfIntRect rect);
int hover_check(button_t *button, sfRenderWindow *window, sfEvent *event);
void clicked_check(button_t *button, sfRenderWindow *window);
void destroy_button(button_t *button);

#endif /* !BUTTON_H_ */