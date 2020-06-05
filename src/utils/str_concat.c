/*
** EPITECH PROJECT, 2020
** str concat
** File description:
** concat strings
*/

#include <stdlib.h>
#include "my.h"

char *str_concat(char *str1, char *str2)
{
    int len1 = my_strlen(str1);
    int len2 = my_strlen(str2);
    char *dest = malloc(sizeof(char) * (len1 + len2 + 1));
    int i = 0;

    dest[len1 + len2] = 0;
    for (int j = 0; str1[i] != 0; ++j) {
        dest[i] = str1[j];
        ++i;
    }
    for (int j = 0; str2[j] != 0; ++j) {
        dest[i] = str2[j];
        ++i;
    }
    return (dest);
}