/*
** COBRA CODING CLUB PROJECT
** client
** File description:
** winner
*/

#include <stdlib.h>
#include "game.h"
#include "game/proc.h"
#include "list.h"

/*
 * Sets the winner and lowers the game's 'live' flag.
 */
void game_proc_winner(game_t *ga, list_t *msg)
{
	if (list_get_size(msg) == 1)
		ga->ga_id_winner = atof(msg->l_start->n_data);
	ga->ga_live = false;
}
