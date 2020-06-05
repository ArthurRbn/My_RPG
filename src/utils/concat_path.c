/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** concat two path
*/

#include <stdlib.h>

char *concat_path(char *str1, char *str2)
{
    int i = 0;
    int y = 0;
    char *concat = NULL;

    for (i = 0; str1[i] != 0; ++i);
    for (y = 0; str2[y] != 0; ++y);
    if (str1[i - 1] != '/')
        ++i;
    concat = malloc(sizeof(char) * (i + y + 1));
    for (i = 0; str1[i] != 0; ++i) {
        concat[i] = str1[i];
    }
    if (concat[i - 1] != '/') {
        concat[i] = '/';
        ++i;
    }
    for (y = 0; str2[y] != 0; ++y) {
        concat[i + y] = str2[y];
    }
    concat[i + y] = 0;
    return (concat);
}