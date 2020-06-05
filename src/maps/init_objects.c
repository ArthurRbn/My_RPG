/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** init objects on the map
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include "maps.h"
#include "my.h"

void set_obj_pos(block_t ***obj)
{
    sfVector2f pos;
    sfIntRect rect;

    pos.x = 0;
    pos.y = 0;
    for (int i = 0; obj[i] != NULL; ++i) {
        pos.y = 89 * 0.54 * i;
        for (int j = 0; obj[i][j] != NULL; ++j) {
            if (obj[i][j]->id != -16) {
                pos.x = 65 * j;
                pos.x += (i % 2 == 1)? 66 / 2 : 0;
                rect = sfSprite_getTextureRect(obj[i][j]->sprite);
                sfSprite_setOrigin(obj[i][j]->sprite, set_vector(rect.width / 2, rect.height / 2));
                sfSprite_setPosition(obj[i][j]->sprite, pos);
                sfSprite_setScale(obj[i][j]->sprite, set_vector(1.6, 1.6));
            }
        }
    }
}

block_t ***set_objects(block_t ***obj, char **tab, char **tile_path)
{
    int id = 0;

    for (int i = 0; obj[i] != NULL; ++i)
        for (int j = 0; obj[i][j] != NULL; ++j) {
            id = tab[i][j] - 48;
            obj[i][j]->id = id;
            if (id == -16) {
                obj[i][j]->texture = NULL;
                obj[i][j]->sprite = NULL;
            } else {
                obj[i][j]->texture = sfTexture_createFromFile(tile_path[id], NULL);
                obj[i][j]->sprite = sfSprite_create();
                sfSprite_setTexture(obj[i][j]->sprite, obj[i][j]->texture, sfTrue);
            }
        }
    set_obj_pos(obj);
    free_tab(tab);
    return (obj);
}

block_t ***get_objects(char *file, char **obj_path)
{
    char **tab = get_file(file);
    block_t ***obj = NULL;
    int lines = 0;
    int len = 0;

    if (!tab)
        return (NULL);
    for (lines = 0; tab[lines] != NULL; ++lines);
    obj = malloc(sizeof(block_t **) * (lines + 1));
    for (int i = 0; i < lines; ++i) {
        for (len = 0; tab[i][len] != 0; ++len);
        obj[i] = malloc(sizeof(block_t *) * (len + 1));
        for (int j = 0; j < len; ++j)
            obj[i][j] = malloc(sizeof(block_t));
        obj[i][len] = NULL;
    }
    obj[lines] = NULL;
    obj = set_objects(obj, tab, obj_path);
    return (obj);
}

block_t ***init_objects(char *file)
{
    char **obj_path = get_file("src/media/objects.txt");
    block_t ***objects = NULL;

    objects = get_objects(concat_path(file, "tileobj.txt"), obj_path);
    free_tab(obj_path);
    return (objects);
}