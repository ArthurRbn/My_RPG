/*
** EPITECH PROJECT, 2019
** my_put_nbr
** File description:
** put number
*/
#include <stdlib.h>
#include <stdio.h>
#include "my.h"

char *recal(char *str, int lon, int dg)
{
    int i;

    for (i = 0; str[0] == 0; ++i) {
        for (i = 0; i < lon - 1; ++i) {
            str[i] = str[i + 1];
            i = i % (lon - 1);
        }
    }
    str[dg] = '\0';
    return (str);
}

int count_digits(int *save)
{
    int digits = 2;

    for (; *save > 0;) {
        *save = *save / 10;
        ++digits;
    }
    return (digits);
}

char *nbr_str(int nb)
{
    int save = nb;
    int digits = count_digits(&save);
    char *str = malloc(sizeof(char) * digits);
    int mod = 0;
    int i = 0;

    for (i = 0; i < digits; ++i)
        str[i] = 0;
    --i;
    for (; nb > 0; --i) {
        save += 1;
        mod = nb % 10;
        nb = nb / 10;
        str[i] = mod + 48;
    }
    if (digits > 2)
        str = recal(str, digits, save);
    if (str[0] == 0)
        return (my_strdup("0"));
    return (str);
}
