/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** functions to get the content of a file
*/

#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "my.h"

int count_lines(char *file)
{
    int fd = open(file, O_RDONLY);
    int lines = 1;
    char *buff = NULL;
    char *old = NULL;

    if (fd == -1)
        return (0);
    buff = get_next_line(fd);
    old = buff;
    while (buff != NULL) {
        buff = get_next_line(fd);
        free(buff);
        ++lines;
    }
    free(old);
    close(fd);
    return (lines);
}

char **get_file(char *file)
{
    int fd = open(file, O_RDONLY);
    char **content = NULL;
    int lines = count_lines(file);

    if (fd == -1)
        return (NULL);
    content = malloc(sizeof(char *) * (lines + 1));
    for (int i = 0; i < lines; ++i)
        content[i] = get_next_line(fd);
    content[lines] = NULL;
    close(fd);
    return (content);
}