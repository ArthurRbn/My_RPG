/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** initialize quests
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include "game.h"
#include "quests.h"
#include "my.h"

void *init_npc_quest(char **detail)
{
    npc_quest_t *new = malloc(sizeof(npc_quest_t));

    if (!new)
        return (NULL);
    new->npc = my_strdup(detail[3]);
    return (new);
}

void *init_kill_quest(char **detail)
{
    kill_quest_t *new = malloc(sizeof(kill_quest_t));

    if (!new)
        return (NULL);
    new->goal = my_getnbr(detail[3]);
    new->killed = 0;
    return (new);
}

quest_slot_t *init_quest_slot(quest_slot_t *next, char *config)
{
    char **detail = str_to_array(config);
    quest_slot_t *slot = malloc(sizeof(quest_slot_t));
    void *(*init_func[])(char **) = {*init_kill_quest, *init_npc_quest};

    if (!slot || !detail)
        return (next);
    slot->type = my_getnbr(detail[0]);
    slot->title = my_strdup(detail[1]);
    for (int i = 0; slot->title[i] != 0; ++i)
        if (slot->title[i] == '_')
            slot->title[i] = ' ';
    slot->xp = my_getnbr(detail[2]);
    slot->active = TRUE;
    slot->next = next;
    slot->quest = init_func[slot->type](detail);
    free_tab(detail);
    if (!slot->quest)
        return (next);
    return (slot);
}

quest_slot_t *get_quests(void)
{
    quest_slot_t *list = NULL;
    char **config = get_file("src/media/quests.txt");

    if (!config)
        return (NULL);
    for (int i = 0; config[i] != NULL; ++i)
        list = init_quest_slot(list, config[i]);
    free_tab(config);
    return (list);
}