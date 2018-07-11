/*
** COBRA CODING CLUB PROJECT
** client
** File description:
** find_best_dist
*/

#include "game.h"

int strat_find_best_dist(game_t *ga)
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
