/*
** EPITECH PROJECT, 2019
** get number
** File description:
** get number
*/
#include <stdio.h>
#include "my.h"

int my_getnbr(char *src)
{
    long res = 0;
    int lon = my_strlen(src);
    int mult = 1;

    for (int i = lon - 1; i >= 0; --i) {
        if (src[i] == '-') {
            res = res * -1;
        } else {
            res = res + ((src[i] - 48) * mult);
            mult = mult * 10;
        }
    }
    return (res);
}