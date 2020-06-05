/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** sfml utils
*/

#include <SFML/Graphics.h>

int is_sprite_clicked(sfSprite *sprite, sfRenderWindow *win)
{
    sfFloatRect bounds = sfSprite_getGlobalBounds(sprite);
    sfVector2f pos = sfRenderWindow_mapPixelToCoords(win,
    sfMouse_getPositionRenderWindow(win), sfRenderWindow_getView(win));

    if (sfFloatRect_contains(&bounds, pos.x, pos.y) == sfTrue)
        return (1);
    return (0);
}

sfText *create_text(char *str, float x, float y, sfFont *font)
{
    sfText *text = sfText_create();
    sfVector2f pos;

    if (!str)
        return (NULL);
    pos.x = x;
    pos.y = y;
    sfText_setString(text, str);
    sfText_setFont(text, font);
    sfText_setPosition(text, pos);
    sfText_setColor(text, sfBlack);
    return (text);
}

sfVector2f set_vector(float x, float y)
{
    sfVector2f vector;

    vector.x = x;
    vector.y = y;
    return (vector);
}

sfIntRect set_rect(float height, float width)
{
    sfIntRect rect;

    rect.left = 0;
    rect.top = 0;
    rect.height = height;
    rect.width = width;
    return (rect);
}