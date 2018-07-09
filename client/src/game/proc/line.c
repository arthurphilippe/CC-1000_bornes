/*
** EPITECH PROJECT, 2018
** client
** File description:
** line
*/

#include "game.h"
#include "game/proc.h"

const proc_key_t PROC_MSG_MAP[] = {
	{"id", NULL},
	{"lsplayer", NULL},
	{"playerstate", NULL},
	{"lscards", NULL},
	{"forfeit", NULL},
	{"winner", NULL},
};

/*
 * Processes one server message and applies changes to the game.
 */
void game_proc_line(game_t *ga, const char *line) {}
