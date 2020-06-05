/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** actualize interface
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include "game.h"
#include "player.h"
#include "my.h"

void display_ui(game_t *game, sfRenderWindow *window)
{
    sfRenderWindow_drawSprite(window, game->ui->sprite, NULL);
    if (game->ui->health != NULL)
        sfRenderWindow_drawText(window, game->ui->health, NULL);
    if (game->ui->xp != NULL)
        sfRenderWindow_drawText(window, game->ui->xp, NULL);
    if (game->ui->attack != NULL)
        sfRenderWindow_drawText(window, game->ui->attack, NULL);
}

void set_ui2(game_t *game, sfRenderWindow *window)
{
    sfVector2f pos = sfRenderWindow_mapPixelToCoords(window,
    (sfVector2i){20, 20}, game->main_view);

    sfSprite_setPosition(game->ui->sprite, pos);
    pos.y += 130;
    pos.x += 30;
    if (game->ui->attack != NULL)
        sfText_destroy(game->ui->attack);
    if (game->player->attack_time >= 100)
        game->ui->attack = create_text("attack: ready", pos.x, pos.y, game->dialog->font);
    else
        game->ui->attack = create_text("attack: not ready", pos.x, pos.y, game->dialog->font);
}

void set_ui(game_t *game, sfRenderWindow *window)
{
    char *xp;
    sfVector2f pos = sfRenderWindow_mapPixelToCoords(window, (sfVector2i){50, 50}, game->main_view);

    if (game->ui->health != NULL)
        sfText_destroy(game->ui->health);
    game->ui->health = create_text(str_concat("health: ", nbr_str(game->player->stats->hp)), pos.x, pos.y, game->dialog->font);
    pos.y += 50;
    xp = concat_path(nbr_str(game->player->stats->xp), nbr_str(game->player->stats->lvl * 35));
    if (game->ui->xp != NULL)
        sfText_destroy(game->ui->xp);
    game->ui->xp = create_text(str_concat("xp: ", xp), pos.x, pos.y, game->dialog->font);
    set_ui2(game, window);
    free(xp);
}

interface_t *init_ui(void)
{
    interface_t *ui = malloc(sizeof(interface_t));

    if (ui == NULL)
        return (NULL);
    ui->attack = NULL;
    ui->xp = NULL;
    ui->health = NULL;
    ui->sprite = sfSprite_create();
    ui->texture = sfTexture_createFromFile("src/media/minimap_box.png", NULL);
    if (!ui->texture || !ui->sprite)
        return (NULL);
    sfSprite_setTexture(ui->sprite, ui->texture, sfTrue);
    sfSprite_setScale(ui->sprite, (sfVector2f){1.2, 2.7});
    return (ui);
}

void destroy_ui(interface_t *ui)
{
    sfText_destroy(ui->attack);
    sfText_destroy(ui->health);
    sfText_destroy(ui->xp);
    sfTexture_destroy(ui->texture);
    sfSprite_destroy(ui->sprite);
    free(ui);
}