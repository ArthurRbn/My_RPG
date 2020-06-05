/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** math utils
*/

#include <SFML/Graphics.h>
#include <math.h>
#include "my.h"

float get_distance(sfSprite *sprite1, sfSprite *sprite2)
{
    sfVector2f pos1 = sfSprite_getPosition(sprite1);
    sfVector2f pos2 = sfSprite_getPosition(sprite2);
    int adjacent = pos1.x - pos2.x;
    int oppose = pos1.y - pos2.y;
    float hypotenuse = hypot(adjacent, oppose);

    return (hypotenuse);
}

float get_blocked_direction(sfSprite *player, sfSprite *obj, int id)
{
    sfVector2f pos_player = sfSprite_getPosition(player);
    sfVector2f pos_obj = sfSprite_getPosition(obj);
    int delta_x = pos_player.x - pos_obj.x;
    int delta_y = pos_player.y - pos_obj.y;

    if (id > 8)
        return (4);
    if (delta_x > 0 && delta_y > 0)
        return (0);
    else if (delta_x < 0 && delta_y > 0)
        return (1);
    if (delta_x < 0 && delta_y < 0)
        return (2);
    else if (delta_x > 0 && delta_y < 0)
        return (3);
    return (4);
}