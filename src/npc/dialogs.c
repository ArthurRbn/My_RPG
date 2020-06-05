/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** dialogs animation
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include "npc.h"
#include "my.h"

dialog_t *init_dialog(void)
{
    dialog_t *dialog = malloc(sizeof(dialog_t));

    if (!dialog)
        return (NULL);
    dialog->line1 = NULL;
    dialog->line2 = NULL;
    dialog->refresh = 1;
    dialog->line = 0;
    dialog->texture = sfTexture_createFromFile("src/media/textbox.png", NULL);
    dialog->sprite = sfSprite_create();
    sfSprite_setTexture(dialog->sprite, dialog->texture, sfTrue);
    sfSprite_setScale(dialog->sprite, set_vector(1.6f, 1.2));
    sfSprite_setPosition(dialog->sprite, set_vector(800, 600));
    dialog->font = sfFont_createFromFile("src/media/police.ttf");
    dialog->npc = NULL;
    return (dialog);
}

int load_text(dialog_t *data, npc_t *npc)
{
    if (data->refresh == 0)
        return (0);
    data->refresh = 0;
    if (data->line1 != NULL) {
        sfText_destroy(data->line1);
        data->line1 = NULL;
    }
    if (data->line2 != NULL) {
        sfText_destroy(data->line2);
        data->line2 = NULL;
    }
    if (npc->dialog[data->line] == NULL)
        return (1);
    data->line1 = create_text(npc->dialog[data->line], 800, 300, data->font);
    data->line += 1;
    if (data->line1 == NULL)
        return (1);
    data->line2 = create_text(npc->dialog[data->line], 800, 300, data->font);
    data->line += 1;
    return (0);
}

void display_dialog(dialog_t *dialog, sfRenderWindow *window, game_t *game)
{
    sfRenderWindow_clear(window, sfBlack);
    display_elements(game->map, window, game);
    sfRenderWindow_drawSprite(window, game->minimap->sprite, NULL);
    sfRenderWindow_drawSprite(window, dialog->sprite, NULL);
    if (dialog->line1 != NULL) {
        sfRenderWindow_drawText(window, dialog->line1, NULL);
    }
    if (dialog->line2 != NULL) {
        sfRenderWindow_drawText(window, dialog->line2, NULL);
    }
    sfRenderWindow_setView(window, game->minimap->view);
    display_elements(game->map, window, game);
    sfRenderWindow_display(window);
}

void place_ui(sfRenderWindow *window, game_t *game)
{
    sfVector2i map_pos;
    sfVector2f box_pos;

    map_pos.x = 700;
    map_pos.y = 600;
    box_pos = sfRenderWindow_mapPixelToCoords(window, map_pos, game->main_view);
    sfSprite_setPosition(game->dialog->sprite, box_pos);
    box_pos.x += 10;
    box_pos.y += 10;
    if (game->dialog->line1 != NULL)
        sfText_setPosition(game->dialog->line1, box_pos);
    box_pos.y += 35;
    if (game->dialog->line2 != NULL)
        sfText_setPosition(game->dialog->line2, box_pos);
    sfRenderWindow_setView(window, game->main_view);
}

void dialog(game_t *game, sfRenderWindow *window, sfEvent *event)
{
    int state = 0;
    sfTime timer;
    float time = 0;

    sfSound_play(game->sounds->hello);
    actualize_quests(game->quests, 1, game->dialog->npc->name, game->player);
    while (state == 0 && sfRenderWindow_isOpen(window) == sfTrue) {
        state = load_text(game->dialog, game->dialog->npc);
        place_ui(window, game);
        display_dialog(game->dialog, window, game);
        event_handling_dialog(game->dialog, event, window);
        sfClock_restart(game->clock);
        while (state == 0 && time < 200 && game->dialog->line2 != NULL) {
            timer = sfClock_getElapsedTime(game->clock);
            time = timer.microseconds / 10000;
        }
        time = 0;
    }
    sfSound_play(game->sounds->bye);
    reset_dialog(game);
}