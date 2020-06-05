/*
** EPITECH PROJECT, 2020
** actualize buttons state
** File description:
** actualize buttons state
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include "my.h"
#include "button.h"

int release(sfEvent *event)
{
    if (event->mouseButton.type == sfEvtMouseButtonReleased)
        return (1);
    return (0);
}

void clicked_check(button_t *button, sfRenderWindow *win)
{
    sfFloatRect *bound = malloc(sizeof(sfFloatRect));
    sfVector2f pos = sfRenderWindow_mapPixelToCoords(win,
    sfMouse_getPositionRenderWindow(win), sfRenderWindow_getView(win));
    sfBool state = sfTrue;
    sfIntRect rect = sfSprite_getTextureRect(button->sprite);

    *bound = sfSprite_getGlobalBounds(button->sprite);
    state = sfFloatRect_contains(bound, pos.x, pos.y);
    rect.left = rect.width * 2;
    if (state == sfTrue) {
        sfSprite_setTextureRect(button->sprite, rect);
        button->pressed = 1;
    }
}

int hover_check(button_t *button, sfRenderWindow *win, sfEvent *event)
{
    sfFloatRect bound = sfSprite_getGlobalBounds(button->sprite);
    sfIntRect rect = sfSprite_getTextureRect(button->sprite);
    sfBool state = sfTrue;
    sfVector2f pos = sfRenderWindow_mapPixelToCoords(win,
    sfMouse_getPositionRenderWindow(win), sfRenderWindow_getView(win));

    state = sfFloatRect_contains(&bound, pos.x, pos.y);
    rect.left = rect.width;
    if (state == sfTrue && button->pressed == 0)
        sfSprite_setTextureRect(button->sprite, rect);
    else if (state == sfTrue && (button->pressed == 1 && release(event) == 1)) {
        sfSprite_setTextureRect(button->sprite, rect);
        button->pressed = 0;
        return (1);
    }
    else if (state == sfFalse) {
        rect.left = 0;
        sfSprite_setTextureRect(button->sprite, rect);
    }
    return (0);
}

button_t *init_button(char *file, sfVector2f pos, sfIntRect rect)
{
    button_t *button = malloc(sizeof(button_t));

    button->texture = sfTexture_createFromFile(file, NULL);
    button->sprite = sfSprite_create();
    if (!button->texture || !button->sprite)
        return (NULL);
    sfSprite_setTexture(button->sprite, button->texture, sfTrue);
    sfSprite_setTextureRect(button->sprite, rect);
    button->pos = pos;
    sfSprite_setPosition(button->sprite, button->pos);
    button->pressed = 0;
    return (button);
}

void destroy_button(button_t *button)
{
    sfTexture_destroy(button->texture);
    sfSprite_destroy(button->sprite);
    free(button);
}