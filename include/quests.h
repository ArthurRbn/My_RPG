/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** quests
*/

#ifndef QUESTS_H_
#define QUESTS_H_

#include <SFML/Graphics.h>

#define KILL_QUEST 0
#define NPC_QUEST 1
#define NB_QUESTS 10

typedef struct npc_quest_s
{
    char *npc;
    int finished;
} npc_quest_t;

typedef struct kill_quest_s
{
    int killed;
    int goal;
    int finished;
} kill_quest_t;

typedef struct quest_slot_s
{
    int type;
    int active;
    char *title;
    void *quest;
    int xp;
    struct quest_slot_s *next;
} quest_slot_t;

quest_slot_t *get_quests(void);
void actualize_quests(quest_slot_t *quests, int type, char *npc, player_t *p);

#endif /* !QUESTS_H_ */