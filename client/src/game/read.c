/*
** COBRA CODING CLUB PROJECT
** client
** File description:
** read
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "game.h"
#include "game/proc.h"
#include "stolist.h"

static int read_and_fill_queue(game_t *ga, list_t *msgq)
{
	char buff[513];
	int r = read(ga->ga_socketfd, buff, 512);

	if (r > 0) {
		buff[r] = 0;
		stolist_existing(msgq, buff, "\r\n");
	}
	return (r);
}

bool game_read(game_t *ga)
{
	list_t *msgq = list_create(free);
	int status = 0;
	int ret;

	if (!msgq) return false;
	while (!status && (ret = read_and_fill_queue(ga, msgq))) {
		while (list_get_size(msgq)) {
			if (!strcmp(list_get_front(msgq), "your_turn"))
				status = 1;
			game_proc(ga, list_get_front(msgq));
			list_pop_front(msgq);
		}
	}
	if (ret <= 0) status = -1;
	list_destroy(msgq);
	return ((status == 1));
}
