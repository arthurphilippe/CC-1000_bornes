/*
** COBRA CODING CLUB PROJECT
** client
** File description:
** main
*/

#include <stdio.h>
#include "game.h"
#include "strat.h"

int main(int ac, char **av)
{
	game_t *ga;
	if (ac != 2) {
		dprintf(2, "%s\n", "too much or to few arguments");
		return (84);
	}
	ga = game_create();
	game_connect(ga, av[1]);
	if (!ga->ga_live) {
		dprintf(2, "%s\n", "failed to connect, exiting!");
		game_delete(ga);
		return (84);
	}
	dprintf(ga->ga_socketfd, "%s\n", "hello jafar");
	while (game_read(ga)) {
		dprintf(2, "loop\n");
		strat_select_and_run(ga);
	}
	game_delete(ga);
}
