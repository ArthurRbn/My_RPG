##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile
##

LDFLAGS	=	-lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio -lm
CFLAGS	+=	-Iinclude -Wall -Wextra

NAME	=	my_rpg

SRC	=	src/utils/my_getnbr.c						\
		src/utils/my_putchar.c						\
		src/utils/my_putstr.c 						\
		src/utils/my_strlen.c 						\
		src/utils/str_concat.c						\
		src/utils/my_strdup.c 						\
		src/utils/get_next_line.c					\
		src/utils/nbr_to_str.c						\
		src/utils/get_file.c						\
		src/utils/concat_path.c						\
		src/utils/free_tab.c						\
		src/utils/sfml_utils.c						\
		src/utils/str_to_array.c					\
		src/utils/my_strcmp.c						\
		src/maps/free_map.c							\
		src/maps/init_map.c							\
		src/maps/init_objects.c						\
		src/maps/map.c								\
		src/player/player.c							\
		src/player/init_player.c					\
		src/player/free_player_elems.c				\
		src/player/move_player.c					\
		src/player/math_utils.c						\
		src/player/camera.c							\
		src/player/player_attack.c					\
		src/event_handling/event_handling.c			\
		src/event_handling/keyboard_handling.c		\
		src/game/init_game.c						\
		src/game/game.c								\
		src/game/restart_game.c						\
		src/particle_system/init_particles.c		\
		src/particle_system/particle_animation.c	\
		src/particle_system/px_particles_animation.c\
		src/particle_system/init_px_particles.c		\
		src/particle_system/particle_utils.c		\
		src/npc/init_npc.c							\
		src/npc/npc_animation.c						\
		src/npc/dialogs.c							\
		src/enemies/enemies.c						\
		src/enemies/init_enemies.c					\
		src/enemies/enemies_utils.c					\
		src/enemies/enemies_animation.c				\
		src/enemies/enemies_standby.c				\
		src/interface/ui.c							\
		src/quests/init_quests.c					\
		src/quests/quests.c							\
		src/sounds/init_sounds.c					\
		src/buttons/buttons.c						\
		src/menus/pause_menu.c						\
		src/menus/init_pause.c						\
		src/menus/settings_menu.c					\
		src/menus/init_settings.c					\
		src/menus/main_menu.c						\
		src/menus/init_main_menu.c					\
		src/menus/stat_menu.c						\
		src/menus/init_stat_menu.c					\
		src/menus/stat_menu_utils.c					\
		src/menus/menus.c							\
		src/menus/init_how_to_play.c				\
		src/inventory/init_items.c					\
		src/inventory/items_utils.c					\
		src/free_mem/destroy.c						\
		src/free_mem/destroy_utils.c				\
		src/main.c									\

OBJ	=	$(SRC:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJ)
	gcc -O2 -o $(NAME) $(OBJ) $(CFLAGS) $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re