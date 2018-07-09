/*
** EPITECH PROJECT, 2018
** client
** File description:
** line
*/

#include "game/proc.h"
#include "game.h"
#include "stolist.h"
#include "string.h"

/**
 * Map of the known server messages and their associated callbacks.
 */
const proc_key_t PROC_MSG_MAP[] = {
	{"id", game_proc_id},
	{"lsplayer", NULL},
	// {"lsplayer", game_proc_lsplayers},
	{"playerstate", game_proc_playerstate},
	{"lscards", game_proc_lscards},
	{"forfeit", game_proc_winner},
	{"winner", game_proc_winner},
	{NULL, NULL},
};

/**
 * Tries to match key with the current message
 */
static bool check_and_call(
	game_t *ga, const proc_key_t *key, list_t *msg, const char *front)
{
	if (!strcmp(key->pk_str, front)) {
		if (key->pk_func) {
			list_pop_front(msg);
			key->pk_func(ga, msg);
		};
		return (true);
	}
	return (false);
}

/**
 * Processes one server message and applies changes to the game.
 */
void game_proc(game_t *ga, const char *line)
{
	list_t *split_msg = stolist(line, " ");
	const char *front;

	if (!split_msg) return;
	if (!list_get_size(split_msg)) {
		list_destroy(split_msg);
		return;
	}
	front = split_msg->l_start->n_data;
	for (unsigned int i = 0; PROC_MSG_MAP[i].pk_str; i += 1)
		if (check_and_call(ga, &PROC_MSG_MAP[i], split_msg, front))
			return;
	list_destroy(split_msg);
}
