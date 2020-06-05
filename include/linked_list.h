/*
** EPITECH PROJECT, 2020
** MYL_my_rpg_2019
** File description:
** linked list
*/

#ifndef LINKED_LIST_
#define LINKED_LIST_

#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <SFML/Window.h>
#include <SFML/Audio.h>
#include <stdio.h>

typedef struct linked_list_s
{
    sfSprite *sprite;
    sfVector2f position;
    int id;
    struct linked_list_s *next;
} linked_list_t;

#endif /* !LINKED_LIST_ */
