/*
** COBRA CODING CLUB PROJECT
** client
** File description:
** winner
*/

#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "game/proc.h"
#include "list.h"

/*
 * Sets the winner and lowers the game's 'live' flag.
 */
void game_proc_winner(game_t *ga, list_t *msg)
{
	if (list_get_size(msg) == 1) {
		ga->ga_id_winner = atof(msg->l_start->n_data);
		if (ga->ga_id_winner == ga->ga_id)
			dprintf(1, "%s\n", " --> You won!\n");
		else
			dprintf(1, "%s\n", " --> You lost...\n");
	} else {
		dprintf(1, "%s\n",
			" --> Everyone but you has declared forfeit.");
	}
	ga->ga_live = false;
}
