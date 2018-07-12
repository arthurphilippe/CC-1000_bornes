/*
** COBRA CODING CLUB PROJECT
** client
** File description:
** main
*/

#include <stdio.h>
#include "game.h"

int start(const char *arg);
int select_and_run(game_t *ga);
int strategy_run(game_t *ga);

int main(int ac, char **av)
{
	int ret;

	if (ac != 2) {
		dprintf(2, "%s\n", "too much or to few arguments");
		ret = 84;
	} else {
		ret = start(av[1]);
	}
	return (ret);
}

int start(const char *arg)
{
	game_t *ga;
	int ret = 0;

	ga = game_create();
	game_connect(ga, arg);
	if (!ga->ga_live) ret = 84;
	while (ga->ga_live && game_read(ga)) {
		strategy_run(ga);
	}
	game_delete(ga);
	return (ret);
}

int strategy_run(game_t *ga)
{
	// Votre stratégie de jeu ici
}
