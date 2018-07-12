/*
** COBRA CODING CLUB PROJECT
** client
** File description:
** use
*/

#include <stdio.h>
#include "game.h"

bool game_use_card(game_t *ga, unsigned int idx)
{
	card_t card = ga->ga_hand[idx];

	if (!ga->ga_ready) return (false);
	dprintf(1, ":: Using card: %d from pos: %d.\n", card, idx);
	dprintf(ga->ga_socketfd, "use %d\n", idx);
	ga->ga_ready = false;
	return (true);
}

bool game_use_attack(game_t *ga, unsigned int idx, unsigned long id_target)
{
	if (!ga->ga_ready) return (false);
	dprintf(ga->ga_socketfd, "attack %d %ld\n", idx, id_target);
	ga->ga_ready = false;
	return (true);
}
