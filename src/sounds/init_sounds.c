/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** initalize sounds
*/

#include <stdlib.h>
#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <SFML/System.h>
#include "game.h"

void destroy_sound(sounds_t *sounds)
{
    sfSoundBuffer_destroy(sounds->a_buff);
    sfSoundBuffer_destroy(sounds->b_buff);
    sfSoundBuffer_destroy(sounds->h_buff);
    sfSoundBuffer_destroy(sounds->l_buff);
    sfSoundBuffer_destroy(sounds->i_buff);
    sfSound_destroy(sounds->attack);
    sfSound_destroy(sounds->bye);
    sfSound_destroy(sounds->hello);
    sfSound_destroy(sounds->item);
    sfSound_destroy(sounds->lvl_up);
    sfMusic_destroy(sounds->soundtrack1);
    sfMusic_destroy(sounds->soundtrack2);
    free(sounds);
}

static void config_sounds(sounds_t *sounds)
{
    sfMusic_setLoop(sounds->soundtrack1, sfTrue);
    sfMusic_setLoop(sounds->soundtrack2, sfTrue);
    sfSound_setBuffer(sounds->attack, sounds->a_buff);
    sfSound_setBuffer(sounds->bye, sounds->b_buff);
    sfSound_setBuffer(sounds->lvl_up, sounds->l_buff);
    sfSound_setBuffer(sounds->item, sounds->i_buff);
}

sounds_t *get_sounds(void)
{
    sounds_t *sounds = malloc(sizeof(sounds_t));

    sounds->attack = sfSound_create();
    sounds->a_buff = sfSoundBuffer_createFromFile("src/media/sounds/atk.ogg");
    sounds->hello = sfSound_create();
    sounds->h_buff = sfSoundBuffer_createFromFile("src/media/sounds/hello.ogg");
    sounds->bye = sfSound_create();
    sounds->b_buff = sfSoundBuffer_createFromFile("src/media/sounds/bye.ogg");
    sounds->item = sfSound_create();
    sounds->i_buff = sfSoundBuffer_createFromFile("src/media/sounds/item.ogg");
    sounds->lvl_up = sfSound_create();
    sounds->l_buff = sfSoundBuffer_createFromFile("src/media/sounds/lvlup.ogg");
    sounds->soundtrack1 = sfMusic_createFromFile("src/media/sounds/track1.ogg");
    sounds->soundtrack2 = sfMusic_createFromFile("src/media/sounds/track2.ogg");
    if (!sounds->b_buff || !sounds->bye || !sounds->a_buff || !sounds->attack || !sounds->h_buff || !sounds->hello || !sounds->item || !sounds->i_buff || !sounds->lvl_up || !sounds->l_buff)
        return (NULL);
    config_sounds(sounds);
    return (sounds);
}