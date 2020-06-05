/*
** EPITECH PROJECT, 2020
** str to array
** File description:
** str to array
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

char **malloc_line(char *str, char **tab)
{
    int i = 0;
    int len;

    if (str[0] == 46 && str[1] == 47)
        i += 2;
    for (i = 0; str[i] == 32; ++i);
    for (int x = 0; str[i] != 0 && str[i] != 10; ++x) {
        for (len = 0; str[i] != 0 && str[i] != 32 && str[i] != 10; ++i)
            ++len;
        tab[x] = malloc(sizeof(char) * (len + 1));
        if (str[i] != 0 && str[i] != 10 && str[i] != 32)
            ++i;
        for (; str[i] == 32; ++i);
    }
    return (tab);
}

char **create_tab(char *str)
{
    int i = 1;
    int words = 0;
    char **tab;

    for (i = 0; str[i] == 32; ++i);
    for (; str[i] != 0 && str[i] != 10;) {
        for (; str[i] != 0 && str[i] != 32 && str[i] != 10; ++i);
        ++words;
        if (str[i] != 0 && str[i] != 10 && str[i] != 32)
            ++i;
        for (; str[i] == 32; ++i);
    }
    tab = malloc(sizeof(char *) * (words + 1));
    tab[words] = NULL;
    return (tab);
}

char **str_to_array(char *str)
{
    char **tab = create_tab(str);
    int i = 0;
    int len;

    tab = malloc_line(str, tab);
    for (i = 0; str[i] == 32; ++i);
    if (str[i] == 46 && str[1] == 47)
        i += 2;
    for (int x = 0; str[i] != 0 && str[i] != 10; ++x) {
        for (len = 0; str[i] != 0 && str[i] != 32 && str[i] != 10; ++i) {
            tab[x][len] = str[i];
            ++len;
        }
        tab[x][len] = 0;
        if (str[i] != 0 && str[i] != 10 && str[i] != 32)
            ++i;
        for (; str[i] == 32; ++i);
    }
    return (tab);
}