/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** free char **
*/

#include <unistd.h>
#include <stdlib.h>

void free_tab(char **tab)
{
    if (!tab)
        return;
    for (int i = 0; tab[i] != NULL; ++i)
        free(tab[i]);
    free(tab);
}