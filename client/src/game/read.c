/*
** COBRA CODING CLUB PROJECT
** client
** File description:
** read
*/

#include <stdio.h>
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

static void show_msgq(list_t *msgq)
{
	list_iter_t iter;
	char *tmp;

	if (!list_get_size(msgq)) return;
	printf("%s\n", ":: Showing recieved messages:");
	list_iter_init(&iter, msgq, FWD);
	while ((tmp = list_iter_next(&iter))) {
		printf(" - \"%s\"\n", tmp);
	}
	printf("%s\n", ":: Processing recieved messages...");
}

bool game_read(game_t *ga)
{
	list_t *msgq = list_create(free);
	int status = 0;
	int ret;

	if (!msgq) return false;
	printf("\n%s\n\n", "*** Waiting ***");
	printf("%s\n", ":: Waiting for server messages...");
	while (!status && (ret = read_and_fill_queue(ga, msgq))) {
		show_msgq(msgq);
		while (list_get_size(msgq)) {
			if (!strcmp(list_get_front(msgq), "your_turn"))
				status = 1;
			game_proc(ga, list_get_front(msgq));
			list_pop_front(msgq);
		}
	}
	if (ret <= 0) status = -1;
	list_destroy(msgq);
	if (status == 1) printf("\n%s\n\n", "*** Player's turn ***");
	return ((status == 1));
}
