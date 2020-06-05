/*
** EPITECH PROJECT, 2020
** utils
** File description:
** compare two strings
*/

int my_strcmp(char const *s1, char const *s2)
{
    int i;

    for (i = 0; s1[i] != 0 && s2[i] != 0 && s1[i] == s2[i]; ++i);
    if (s1[i] == s2[i])
        return (1);
    if (s1[i] != s2[i])
        return (0);
    return (1);
}