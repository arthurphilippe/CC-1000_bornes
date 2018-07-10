/*
** COBRA CODING CLUB PROJECT
** client
** File description:
** playerstate
*/

#include <stdlib.h>
#include "game.h"
#include "game/proc.h"
#include "list.h"

/*
 * Sets the value pointed by val to the val contained in the given
 * string
 */
static void set_bool(bool *val, const char *src) { *val = (src[0] == '1'); }

/*
 * Set the next player state
 */
void game_proc_playerstate(game_t *ga, list_t *msg)
{
	player_state_t *ps;
	if (msg->l_size != 8 || ga->ga_player_nb >= 6) return;
	ps = &ga->ga_players[ga->ga_player_nb];
	ps->ps_id = atol(list_get_front(msg));
	list_pop_front(msg);
	ps->ps_dist = atoi(list_get_front(msg));
	list_pop_front(msg);
	ps->ps_incident = atoi(list_get_front(msg));
	list_pop_front(msg);
	set_bool(&ps->ps_limited, list_get_front(msg));
	list_pop_front(msg);
	set_bool(&ps->ps_ace, list_get_front(msg));
	list_pop_front(msg);
	set_bool(&ps->ps_tank, list_get_front(msg));
	list_pop_front(msg);
	set_bool(&ps->ps_puncture_proof, list_get_front(msg));
	list_pop_front(msg);
	set_bool(&ps->ps_prioritised, list_get_front(msg));
	list_pop_front(msg);
	ga->ga_player_nb += 1;
}
