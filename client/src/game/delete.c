/*
** EPITECH PROJECT, 2018
** client
** File description:
** delete
*/

#include <stdlib.h>
#include "game.h"

void game_delete(void *ptr)
{
	game_t *ga = ptr;
	free(ga);
}
