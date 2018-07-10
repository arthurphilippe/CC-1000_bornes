/*
** COBRA CODING CLUB PROJECT
** client
** File description:
** id
*/

#include <stdlib.h>
#include "game.h"
#include "game/proc.h"
#include "list.h"

/*
 * Sets the player's id.
 */
void game_proc_id(game_t *ga, list_t *msg)
{
	if (list_get_size(msg) == 1) ga->ga_id = atof(msg->l_start->n_data);
}
