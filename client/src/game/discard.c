/*
** COBRA CODING CLUB PROJECT
** client
** File description:
** discard
*/

#include <stdio.h>
#include "game.h"

bool game_discard_card(game_t *ga, unsigned int idx)
{
	if (!ga->ga_ready) return (false);
	dprintf(1, ":: Discarding card at pos: %d.\n", idx);
	dprintf(ga->ga_socketfd, "discard %d\n", idx);
	ga->ga_ready = false;
	return (true);
}
