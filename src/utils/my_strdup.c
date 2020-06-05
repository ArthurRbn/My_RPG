/*
** EPITECH PROJECT, 2019
** get a string
** File description:
** my_getstr
*/

#include <stdlib.h>
#include "my.h"

char *my_strdup(char *src)
{
    int len = my_strlen(src);
    char *dest = malloc(sizeof(char) * (len + 1));
    int i = 0;

    if (!dest)
        return (NULL);
    for (i = 0; src[i] != 0; ++i) {
        dest[i] = src[i];
    }
    dest[i] = 0;
    return (dest);
}