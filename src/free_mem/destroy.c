/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** take care of your random access memory
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include "my.h"
#include "quests.h"
#include "player.h"
#include "particles.h"
#include "npc.h"
#include "menus.h"
#include "maps.h"
#include "linked_list.h"
#include "game.h"
#include "enemy.h"
#include "button.h"

void destroy_dialog(dialog_t *dialog)
{
    sfTexture_destroy(dialog->texture);
    sfSprite_destroy(dialog->sprite);
    if (dialog->line1)
        sfText_destroy(dialog->line1);
    if (dialog->line2)
        sfText_destroy(dialog->line2);
    sfFont_destroy(dialog->font);
    free(dialog);
}

void destroy_views(sfView *view, minimap_t *minimap)
{
    sfView_destroy(view);
    sfView_destroy(minimap->view);
    sfTexture_destroy(minimap->texture);
    sfSprite_destroy(minimap->sprite);
    free(minimap);
}

void destroy_menus(menus_t *menus)
{
    destroy_main_menu(menus->start);
    destroy_pause_menu(menus->pause);
    destroy_settings_menu(menus->settings);
    destroy_stat_menu(menus->stats);
    destroy_how_to(menus->how_to);
    free(menus);
}

void destroy_quests(quest_slot_t *quests)
{
    quest_slot_t *prev = quests;
    npc_quest_t *temp;

    while (quests) {
        prev = quests;
        quests = quests->next;
        free(prev->title);
        if (prev->type == 0)
            free(prev->quest);
        else if (prev->type == 1) {
            temp = prev->quest;
            free(temp->npc);
            free(temp);
        }
        free(prev);
    }
}

void ultimate_destroy(game_t *game, sfRenderWindow *window)
{
    sfClock_destroy(game->clock);
    destroy_dialog(game->dialog);
    destroy_sound(game->sounds);
    destroy_views(game->main_view, game->minimap);
    destroy_player(game->player);
    destroy_menus(game->menus);
    destroy_ui(game->ui);
    free_map(game->map);
    destroy_npc(game->npc);
    destroy_quests(game->quests);
    remove_all_enemies(game->enemies);
    destroy_particles(game->particles);
    destroy_effects(game->effects);
    sfRenderWindow_destroy(window);
    free(game);
}