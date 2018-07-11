/*
** COBRA CODING CLUB PROJECT
** client
** File description:
** use
*/

#include <stdio.h>
#include "game.h"

bool game_use_card(game_t *ga, unsigned int idx)
{
	card_t card = ga->ga_hand[idx];
	bool ret = true;

	switch (card) {
	case DefRepair ... Dst200kms:
		dprintf(1, ":: Using card: %d from pos: %d.\n", card, idx);
		dprintf(ga->ga_socketfd, "use %d\n", idx);
		break;
	case HazCarCrash ... HazRedLight:
		dprintf(2, "%s\n",
			" error: you cannot attack with 'game_use_card'."
			" Use 'game_use_attack' instead.");
		break;
	default:
		ret = false;
		dprintf(2, "%s\n", " error: unsuported card\n");
	}
	return (ret);
}

static player_state_t *find_plstate(game_t *ga, unsigned long *id)
{
	for (unsigned int i = 0; i < ga->ga_player_nb; i += 1) {
		if (ga->ga_players[i].ps_id == *id) {
			*id = i;
			return (&ga->ga_players[i]);
		}
	}
	return (NULL);
}

bool game_use_attack_by_id(game_t *ga, unsigned int idx, unsigned long id)
{
	player_state_t *ps = find_plstate(ga, &id);

	if (!ps) {
		dprintf(2, "%s %ld\n", " error: cannot find id:", id);
		return (false);
	}
	return (game_use_attack(ga, idx, id));
}

bool game_use_attack(game_t *ga, unsigned int idx, unsigned int idx_target)
{
	bool ret = true;
	card_t card = ga->ga_hand[idx];
	player_state_t *ps = &ga->ga_players[idx % 6];

	if (ps->ps_incident != NONE) {
		dprintf(2, "%s\n",
			" error: cannot attack someone already in a "
			"predicament\n");
		return (false);
	}
	switch (card) {
	case HazCarCrash ... HazRedLight:
		dprintf(ga->ga_socketfd, "attack %d %d\n", idx, idx_target);
		break;
	default:
		ret = false;
		dprintf(2, "%s\n", " error: unsuported card\n");
	}
	return (ret);
}
