/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** my
*/

#ifndef MY_H
#define MY_H

#define READ_SIZE 2000
#define FALSE 0
#define TRUE 1

#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include "linked_list.h"
#include "npc.h"
#include "game.h"

//event handling
int handle_event(sfEvent *event, sfRenderWindow *window, game_t *game);
void event_handling_dialog(dialog_t *dialog, sfEvent *event,
sfRenderWindow *window);
void keyboard_handling(game_t *game, sfRenderWindow *window);
void handle_main_events(sfEvent *event, sfRenderWindow *window, game_t *game);
void clocked_event(game_t *game);

//particle system
void create_particles(game_t *game, const sfTexture *img,
sfVector2f player_pos);
void add_particle(game_t *game);
void move_particle(particle_t *particles);
void display_particles(game_t *game, sfRenderWindow *window);
px_particle_t *init_px_particles(px_particle_t *next, int *rgb, int width,
int height);
void refresh_all_px(game_t *game);
void draw_effects(sfRenderWindow *win, px_particle_t *effect);
void update_px_particles(int width, int height, px_particle_t *rgb);

//enemies animation
void refresh_enemies(game_t *game);

//npc animation
void display_npc(npc_t *list, sfRenderWindow *window, sfSprite *player);
void move_icon(npc_t *npc);
void dialog(game_t *game, sfRenderWindow *window, sfEvent *event);
void check_npc(game_t *game, sfRenderWindow *window, sfEvent *event);
void reset_dialog(game_t *game);

//init elements
void create_views(game_t *game, sfRenderWindow *window);
player_t *choose_player(sfRenderWindow *window, sfEvent *event, char *name,
game_t *game);
npc_t *init_all_npc(void);
dialog_t *init_dialog(void);
void get_items(npc_t *ch_npc);
void restart_game(game_t *game, sfRenderWindow *window);

//destroy elements
void ultimate_destroy(game_t *game, sfRenderWindow *window);
void destroy_npc(npc_t *list);
int destroy_old_particles(particle_t **particles);
void destroy_px_particle(px_particle_t **effects);
void destroy_particles(particle_t *particle);
void destroy_effects(px_particle_t *effects);
void destroy_quests(quest_slot_t *quests);

//sfml utils
sfIntRect set_rect(float height, float width);
int is_sprite_clicked(sfSprite *sprite, sfRenderWindow *win);
sfText *create_text(char *str, float x, float y, sfFont *font);
sfVector2f set_vector(float x, float y);
float get_distance(sfSprite *sprite1, sfSprite *sprite2);
int check_colision(sfSprite *player, block_t ***obj);

//utils
int my_strlen(char const *str);
int my_getnbr(char *src);
void my_putchar(char c);
void my_putstr(char const *str);
char *str_concat(char *str1, char *str2);
char *get_next_line(int fd);
char *my_strdup(char *src);
char *nbr_str(int nb);
char **get_file(char *file);
char *concat_path(char *str1, char *str2);
char **str_to_array(char *str);
void free_tab(char **tab);
int my_strcmp(char const *s1, char const *s2);

#endif //MY_H
