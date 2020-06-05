/*
** EPITECH PROJECT, 2019
** get next line
** File description:
** get next line
*/

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "my.h"

char *concat_params(char *str1, char *str2)
{
    int i = 0;
    int y = 0;
    char *concat;

    for (i = 0; str1[i] != 0; ++i);
    for (y = 0; str2[y] != 0; ++y);
    concat = malloc(sizeof(char) * (i + y + 1));
    if (!concat)
        return (NULL);
    for (i = 0; str1[i] != 0; ++i) {
        concat[i] = str1[i];
    }
    for (y = 0; str2[y] != 0; ++y) {
        concat[i + y] = str2[y];
    }
    concat[i + y] = 0;
    return (concat);
}

char *set_rest(char *trash, int erase)
{
    char *new_trash;
    int i = 40;
    int j = 0;

    erase += 1;
    for (i = 0; trash[erase + i] != 0; ++i);
    new_trash = malloc(sizeof(char) * i + 1);
    if (!new_trash)
        return (NULL);
    for (j = 0; trash[erase + j] != 0; ++j)
        new_trash[j] = trash[erase + j];
    new_trash[j] = 0;
    free(trash);
    return (new_trash);
}

char *copy_return(char **trash)
{
    char *ret;
    int i = 0;
    int x = 0;

    for (i = 0; trash[0][i] != 0 && trash[0][i] != 10; ++i);
    ret = malloc(sizeof(char) * i + 1);
    if (!ret)
        return (NULL);
    for (x = 0; trash[0][x] != 0 && trash[0][x] != 10; ++x)
        ret[x] = trash[0][x];
    x -= (trash[0][x] == 0)? 1 : 0;
    trash[0] = set_rest(trash[0], x);
    ret[i] = 0;
    return (ret);
}

char *choose_return(int fd, char **trash, int bytes)
{
    int i = 0;
    int state = 0;
    char *retour;
    char *buff;

    while (state == 0 && bytes == READ_SIZE) {
        for (i = 0; trash[0][i] != 10 && trash[0][i] != 0; ++i);
        state = trash[0][i];
        if (state == 0) {
            buff = malloc(sizeof(char) * READ_SIZE + 1);
            bytes = read(fd, buff, READ_SIZE);
            buff[bytes] = 0;
            trash[0] = concat_params(*trash, buff);
            free(buff);
        }
        for (i = 0; trash[0][i] != 10 && trash[0][i] != 0; ++i);
        if (i == 0 && bytes == 0)
            return (NULL);
    }
    retour = copy_return(trash);
    return (retour);
}

char *get_next_line(int fd)
{
    static char *trash;
    static int calls = 0;
    char *buff;
    int bytes = READ_SIZE;

    if (calls == 0) {
        trash = malloc(sizeof(char) * READ_SIZE + 1);
        if (!trash)
            return (NULL);
        bytes = read(fd, trash, READ_SIZE);
        trash[bytes] = 0;
    }
    ++calls;
    buff = choose_return(fd, &trash, bytes);
    return (buff);
}