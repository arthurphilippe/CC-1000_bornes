/*
** COBRA CODING CLUB PROJECT
** client
** File description:
** strat_select_and_run
*/

#include "game.h"
#include "strat.h"

static int find_card(game_t *ga, card_t card)
{
	int i;
	for (i = 0; i < 6; i++) {
		if (ga->ga_hand[i] == card) {
			return (i);
		}
	}
	return (-1);
}

int strat_select_and_run(game_t *ga)
{
	int to_play;

	if (ga->ga_self.ps_incident == HazCarCrash) {
		to_play = find_card(ga, DefRepair);
	} else if (ga->ga_self.ps_incident == HazGasOutage) {
		to_play = find_card(ga, DefGas);
	} else {
		to_play = strat_find_best_dist(ga);
	}
	if (to_play == -1) {
		to_play = find_card(ga, HazCarCrash);
		if (to_play == -1) to_play = find_card(ga, HazGasOutage);
		if (to_play == -1) to_play = find_card(ga, Dst25kms);
		if (to_play == -1) to_play = find_card(ga, DefRepair);
		if (to_play == -1) to_play = find_card(ga, DefGas);
		if (to_play == -1) to_play = find_card(ga, Dst50kms);
		if (to_play == -1) to_play = find_card(ga, Dst75kms);
		if (to_play == -1) to_play = find_card(ga, Dst100kms);
		if (to_play == -1) to_play = find_card(ga, Dst200kms);
		game_discard_card(ga, (to_play != -1) ? to_play : 0);
	} else {
		game_use_card(ga, to_play);
	}
	return (0);
}
