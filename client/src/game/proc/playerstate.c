/*
** EPITECH PROJECT, 2018
** client
** File description:
** playerstate
*/

#include <stdlib.h>
#include "game.h"
#include "game/proc.h"
#include "list.h"

static void set_bool(bool *val, const char *src) { *val = (src[0] == '1'); }

void game_proc_playerstate(game_t *ga, list_t *msg)
{
	if (msg->l_size != 8 || ga->ga_player_nb >= 6) return;
	ga->ga_players[ga->ga_player_nb].ps_id = atol(list_get_front(msg));
	list_pop_front(msg);
	ga->ga_players[ga->ga_player_nb].ps_dist = atoi(list_get_front(msg));
	list_pop_front(msg);
	ga->ga_players[ga->ga_player_nb].ps_incident =
		atoi(list_get_front(msg));
	list_pop_front(msg);
	set_bool(&ga->ga_players[ga->ga_player_nb].ps_limited,
		list_get_front(msg));
	list_pop_front(msg);
	set_bool(&ga->ga_players[ga->ga_player_nb].ps_ace,
		list_get_front(msg));
	list_pop_front(msg);
	set_bool(&ga->ga_players[ga->ga_player_nb].ps_tank,
		list_get_front(msg));
	list_pop_front(msg);
	set_bool(&ga->ga_players[ga->ga_player_nb].ps_puncture_proof,
		list_get_front(msg));
	list_pop_front(msg);
	set_bool(&ga->ga_players[ga->ga_player_nb].ps_prioritised,
		list_get_front(msg));
	list_pop_front(msg);
}
