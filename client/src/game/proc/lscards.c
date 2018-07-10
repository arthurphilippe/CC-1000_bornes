/*
** COBRA CODING CLUB PROJECT
** client
** File description:
** lscards
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "game/proc.h"
#include "list.h"

/*
 * Modifies the player's hand with information recieved by the server.
 *
 * Also clears the player statuses.
 */
void game_proc_lscards(game_t *ga, list_t *msg)
{
	list_iter_t iter;
	unsigned int i = 0;
	const char *tmp;

	if (msg->l_size != 6) return;
	list_iter_init(&iter, msg, FWD);
	while ((tmp = list_iter_next(&iter))) {
		if (isdigit(tmp[0]))
			ga->ga_hand[i++] = atoi(tmp);
		else
			ga->ga_hand[i++] = NONE;
	}
	for (i = 0; i < 6; i += 1) ga->ga_players[i].ps_id = 0;
	ga->ga_player_nb = 0;
}
