/*
** EPITECH PROJECT, 2018
** client
** File description:
** create
*/

#include <stdlib.h>
#include "game.h"

/*
 * Creates an empty game_t object
 */
game_t *game_create(void)
{
	game_t *ga = calloc(1, sizeof(game_t));

	if (!ga) return (NULL);
	ga->ga_live = true;
	for (unsigned int i = 0; i < 6; i += 1) ga->ga_hand[i] = NONE;
	return (ga);
}
