/*
** COBRA CODING CLUB PROJECT
** client
** File description:
** info
*/

#include <stdio.h>
#include "game.h"
#include "game/proc.h"
#include "list.h"

void game_proc_info(game_t *ga, list_t *msg)
{
	(void) ga;
	if (list_get_size(msg)) {
		dprintf(1, "--> Server says\n \'%s\'\n\n",
			(char *) list_get_front(msg));
	}
}
