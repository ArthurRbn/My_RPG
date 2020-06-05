/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** actualize quests
*/

#include <SFML/Graphics.h>
#include "my.h"
#include "game.h"
#include "quests.h"

int handle_kill_quest(quest_slot_t *slot)
{
    kill_quest_t *temp = slot->quest;

    temp->killed += 1;
    if (temp->killed >= temp->goal) {
        temp->finished = TRUE;
        return (0);
    }
    return (1);
}

int handle_npc_quest(quest_slot_t *slot, char *npc)
{
    npc_quest_t *temp = slot->quest;

    if (my_strcmp(temp->npc, npc) == TRUE) {
        temp->finished = TRUE;
        return (0);
    }
    return (1);
}

void actualize_quests(quest_slot_t *quests, int type, char *npc, player_t *p)
{
    quest_slot_t *temp = quests;

    while (temp) {
        if (temp->active == TRUE && temp->type == type && type == 0) {
            temp->active = handle_kill_quest(temp);
            p->stats->xp += (temp->active == FALSE)? temp->xp : 0;
        } else if (temp->active == TRUE && temp->type == type && type == 1) {
            temp->active = handle_npc_quest(temp, npc);
            p->stats->xp += (temp->active == FALSE)? temp->xp : 0;
        }
        temp = temp->next;
    }
}