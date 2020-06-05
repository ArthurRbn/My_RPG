/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** game
*/

#ifndef GAME_H_
#define GAME_H_

#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include "maps.h"
#include "player.h"
#include "particles.h"
#include "enemy.h"
#include "npc.h"
#include "quests.h"
#include "menus.h"

#define GAME 1
#define MAIN_MENU 0
#define PAUSE_MENU 2
#define SETTINGS 3
#define STAT_MENU 4
#define HOW_TO 5
#define QUIT 10

typedef struct sounds_s
{
    sfMusic *soundtrack1;
    sfMusic *soundtrack2;
    sfSound *hello;
    sfSoundBuffer *h_buff;
    sfSound *bye;
    sfSoundBuffer *b_buff;
    sfSound *attack;
    sfSoundBuffer *a_buff;
    sfSound *item;
    sfSoundBuffer *i_buff;
    sfSound *lvl_up;
    sfSoundBuffer *l_buff;
} sounds_t;

typedef struct minimap_s
{
    sfTexture *texture;
    sfSprite *sprite;
    sfView *view;
} minimap_t;

typedef struct interface_s
{
    sfText *health;
    sfText *xp;
    sfText *attack;
    sfTexture *texture;
    sfSprite *sprite;
} interface_t;

typedef struct game_s
{
    map_t *map;
    particle_t *particles;
    px_particle_t *effects;
    player_t *player;
    sfClock *clock;
    sfView *main_view;
    minimap_t *minimap;
    npc_t *npc;
    dialog_t *dialog;
    enemy_t *enemies;
    interface_t *ui;
    quest_slot_t *quests;
    sounds_t *sounds;
    int display;
    menus_t *menus;
} game_t;

sfRenderWindow *init_window(void);
game_t *init_game(sfRenderWindow *window, sfEvent *event, char *name);
void game_loop(sfEvent *event, game_t *game, sfRenderWindow *window);
void move_player(game_t *game, int dir);
void refresh_player(player_t *player, enemy_t *enemy, game_t *game);
void set_attack(game_t *game);
int stay_in_map(map_t *map, int dir, player_t *player);
void manage_view(game_t *game, sfRenderWindow *window);
void display_elements(map_t *map, sfRenderWindow *window, game_t *game);
void display_obj(block_t ***obj, sfRenderWindow *window, sfSprite *player);
interface_t *init_ui(void);
void set_ui(game_t *game, sfRenderWindow *window);
void place_ui(sfRenderWindow *window, game_t *game);
void display_dialog(dialog_t *dialog, sfRenderWindow *window, game_t *game);
void display_ui(game_t *game, sfRenderWindow *window);
void destroy_ui(interface_t *ui);
void set_sprites_positions(player_t *player, enemy_t *enemy);
sounds_t *get_sounds(void);
void destroy_sound(sounds_t *sounds);
menus_t *get_menus(void);
void main_menu(game_t *game, sfRenderWindow *window, sfEvent *event);
void pause_menu(game_t *game, sfRenderWindow *window);
void settings_menu(game_t *g, sfRenderWindow *window, sfEvent *event);
void display_settings(options_menu_t *menu, sfRenderWindow *win, game_t *game);
void init_quests_txt(stat_menu_t *menu, sfRenderWindow *window, sfView *view,
game_t *game);
void init_stats_txt(stat_menu_t *menu, sfRenderWindow *window, sfView *view,
game_t *game);
void set_inventory_pos(stat_menu_t *menu, sfRenderWindow *window, sfView *view);
void stat_menu(game_t *game, sfRenderWindow *window);
void item_npc_to_player(inventory_t **inv, npc_t *npc, game_t *game,
sfRenderWindow *window);
void how_to_play(game_t *game, sfRenderWindow *window);

#endif /* !GAME_H_ */