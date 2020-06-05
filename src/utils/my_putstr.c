/*
** EPITECH PROJECT, 2019
** my_putstr
** File description:
** my_putstr
*/
#include "my.h"

void my_putstr(char const *str)
{
    int i = 0;

    while (str[i] != '\0') {
        my_putchar(str[i]);
        i = i + 1;
    }
}