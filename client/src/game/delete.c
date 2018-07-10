/*
** EPITECH PROJECT, 2018
** client
** File description:
** delete
*/

#include <stdlib.h>
#include <unistd.h>
#include "game.h"

/**
 * Game deletion procedure goes here
 */
void game_delete(void *ptr)
{
	game_t *ga = ptr;

	free(ga);
	if (ga->ga_socketfd != 0 && ga->ga_socketfd != -1)
		close(ga->ga_socketfd);
}
