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
		select_and_run(ga);
	}
	game_delete(ga);
	return (ret);
}

int find_card(game_t *ga, card_t card)
{
	int i;
	for (i = 0; i < 6; i++) {
		if (ga->ga_hand[i] == card) {
			return (i);
		}
	}
	return (-1);
}

int find_best_dist(game_t *ga)
{
	int best_idx = -1;
	card_t best_card = NONE;

	for (unsigned int i = 0; i < 6 && best_card != Dst200kms; i++) {
		if (ga->ga_hand[i] >= Dst25kms &&
			(best_card == NONE || ga->ga_hand[i] > best_card)) {
			best_idx = i;
			best_card = ga->ga_hand[i];
		}
	}
	return (best_idx);
}

int select_and_run(game_t *ga)
{
	int to_play;

	if (ga->ga_self.ps_incident == HazCarCrash) {
		to_play = find_card(ga, DefRepair);
	} else if (ga->ga_self.ps_incident == HazGasOutage) {
		to_play = find_card(ga, DefGas);
	} else {
		to_play = find_best_dist(ga);
	}
	if (to_play == -1) {
		game_discard_card(ga, (to_play != -1) ? to_play : 0);
	} else {
		game_use_card(ga, to_play);
	}
	return (0);
}
