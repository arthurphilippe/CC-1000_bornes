/*
** EPITECH PROJECT, 2018
** client
** File description:
** game
*/

#include "game/proc.h"
#include <criterion/assert.h>
#include <criterion/criterion.h>
#include "game.h"

Test(GameProc, Id)
{
	game_t *ga = game_create();

	cr_assert(ga);
	for (unsigned int i = 0; i < 6; i += 1)
		cr_expect_eq(ga->ga_hand[i], NONE);
	cr_expect_eq(ga->ga_player_nb, 0);
	cr_expect_eq(ga->ga_id, 0);

	game_proc(ga, "  ");
	game_proc(ga, "id 12");
	cr_expect_eq(ga->ga_id, 12, "got %ld instead of %ld", ga->ga_id, 12);
	game_proc(ga, "id");
	cr_expect_eq(ga->ga_id, 12, "got %ld instead of %ld", ga->ga_id, 12);
	game_proc(ga, "id 9 r-tyujkl");
	cr_expect_eq(ga->ga_id, 12, "got %ld instead of %ld", ga->ga_id, 12);
	game_delete(ga);
}

Test(GameProc, LsPlayers)
{
	game_t *ga = game_create();

	cr_assert(ga);
	for (unsigned int i = 0; i < 6; i += 1)
		cr_expect_eq(ga->ga_hand[i], NONE);
	cr_expect_eq(ga->ga_player_nb, 0);
	cr_expect_eq(ga->ga_id, 0);

	game_proc(ga, "  ");
	game_proc(ga, "id 12");
	cr_expect_eq(ga->ga_id, 12, "got %ld instead of %ld", ga->ga_id, 12);
	game_proc(ga, "id");
	cr_expect_eq(ga->ga_id, 12, "got %ld instead of %ld", ga->ga_id, 12);
	game_proc(ga, "id 9 r-tyujkl");
	cr_expect_eq(ga->ga_id, 12, "got %ld instead of %ld", ga->ga_id, 12);
	game_proc(ga, "lsplayers 12 45 62");
	cr_expect_eq(ga->ga_player_nb, 0);
	game_delete(ga);
}

Test(GameProc, LsCards)
{
	game_t *ga = game_create();

	cr_assert(ga);
	for (unsigned int i = 0; i < 6; i += 1)
		cr_expect_eq(ga->ga_hand[i], NONE);
	cr_expect_eq(ga->ga_player_nb, 0);
	cr_expect_eq(ga->ga_id, 0);

	game_proc(ga, "id 12");
	cr_expect_eq(ga->ga_id, 12, "got %ld instead of %ld", ga->ga_id, 12);

	game_proc(ga, "lscards 7 15 16 13 0 9");

	cr_expect_eq(ga->ga_hand[0], DefSpareWheel);
	cr_expect_eq(ga->ga_hand[1], Dst50kms);
	cr_expect_eq(ga->ga_hand[2], Dst75kms);
	cr_expect_eq(ga->ga_hand[3], SpePrioritised);
	cr_expect_eq(ga->ga_hand[4], HazCarCrash);
	cr_expect_eq(ga->ga_hand[5], DefGreenLight);

	game_proc(ga, "lscards 0 9 12");
	cr_expect_eq(ga->ga_hand[0], DefSpareWheel);
	cr_expect_eq(ga->ga_hand[1], Dst50kms);
	cr_expect_eq(ga->ga_hand[2], Dst75kms);
	cr_expect_eq(ga->ga_hand[3], SpePrioritised);
	cr_expect_eq(ga->ga_hand[4], HazCarCrash);
	cr_expect_eq(ga->ga_hand[5], DefGreenLight);

	game_proc(ga, "lscards 7 patate 16 20 0 9");
	cr_expect_eq(ga->ga_hand[0], DefSpareWheel);
	cr_expect_eq(ga->ga_hand[1], NONE);
	cr_expect_eq(ga->ga_hand[2], Dst75kms);
	cr_expect_eq(ga->ga_hand[3], NONE);
	cr_expect_eq(ga->ga_hand[4], HazCarCrash);
	cr_expect_eq(ga->ga_hand[5], DefGreenLight);
	game_delete(ga);
}

Test(GameProc, PlayerState)
{
	game_t *ga = game_create();

	cr_assert(ga);
	for (unsigned int i = 0; i < 6; i += 1)
		cr_expect_eq(ga->ga_hand[i], NONE);
	cr_expect_eq(ga->ga_player_nb, 0);
	cr_expect_eq(ga->ga_id, 0);

	game_proc(ga, "id 12");
	cr_expect_eq(ga->ga_id, 12, "got %ld instead of %ld", ga->ga_id, 12);

	game_proc(ga, "playerstate 7 525 2 1 0 1 0 0");
	player_state_t *ps = &ga->ga_players[0];

	cr_expect_eq(ps->ps_id, 7);
	cr_expect_eq(ps->ps_dist, 525);
	cr_expect_eq(ps->ps_incident, HazFlatTire);
	cr_expect_eq(ps->ps_limited, true);
	cr_expect_eq(ps->ps_ace, false);
	cr_expect_eq(ps->ps_tank, true);
	cr_expect_eq(ps->ps_puncture_proof, false);
	cr_expect_eq(ps->ps_prioritised, false);

	game_proc(ga, "playerstate 4 450 0 0 0 0 1 1");
	ps = &ga->ga_players[1];
	cr_expect_eq(ps->ps_id, 4);
	cr_expect_eq(ps->ps_dist, 450);
	cr_expect_eq(ps->ps_incident, HazCarCrash);
	cr_expect_eq(ps->ps_limited, false);
	cr_expect_eq(ps->ps_ace, false);
	cr_expect_eq(ps->ps_tank, false);
	cr_expect_eq(ps->ps_puncture_proof, true);
	cr_expect_eq(ps->ps_prioritised, true);

	game_proc(ga, "playerstate 94 925 20 0 1 0 1 1");
	ps = &ga->ga_players[2];
	cr_expect_eq(ps->ps_id, 94);
	cr_expect_eq(ps->ps_dist, 925);
	cr_expect_eq(ps->ps_incident, NONE);
	cr_expect_eq(ps->ps_limited, false);
	cr_expect_eq(ps->ps_ace, true);
	cr_expect_eq(ps->ps_tank, false);
	cr_expect_eq(ps->ps_puncture_proof, true);
	cr_expect_eq(ps->ps_prioritised, true);
	ps = &ga->ga_players[1];
	cr_expect_eq(ps->ps_id, 4);
	cr_expect_eq(ps->ps_dist, 450);
	cr_expect_eq(ps->ps_incident, HazCarCrash);
	cr_expect_eq(ps->ps_limited, false);
	cr_expect_eq(ps->ps_ace, false);
	cr_expect_eq(ps->ps_tank, false);
	cr_expect_eq(ps->ps_puncture_proof, true);
	cr_expect_eq(ps->ps_prioritised, true);

	game_proc(ga, "playerstate 5 800 20 1 0 1 0 0");
	ps = &ga->ga_players[3];

	cr_expect_eq(ps->ps_id, 5);
	cr_expect_eq(ps->ps_dist, 800);
	cr_expect_eq(ps->ps_incident, NONE);
	cr_expect_eq(ps->ps_limited, true);
	cr_expect_eq(ps->ps_ace, false);
	cr_expect_eq(ps->ps_tank, true);
	cr_expect_eq(ps->ps_puncture_proof, false);
	cr_expect_eq(ps->ps_prioritised, false);

	game_proc(ga, "playerstate 5 900 20 1 0 1 0 0");
	ps = &ga->ga_players[4];

	cr_expect_eq(ps->ps_id, 5);
	cr_expect_eq(ps->ps_dist, 900);
	cr_expect_eq(ps->ps_incident, NONE);
	cr_expect_eq(ps->ps_limited, true);
	cr_expect_eq(ps->ps_ace, false);
	cr_expect_eq(ps->ps_tank, true);
	cr_expect_eq(ps->ps_puncture_proof, false);
	cr_expect_eq(ps->ps_prioritised, false);

	game_proc(ga, "playerstate 5 775 20 1 0 1 0 0");
	ps = &ga->ga_players[5];

	cr_expect_eq(ps->ps_id, 5);
	cr_expect_eq(ps->ps_dist, 775);
	cr_expect_eq(ps->ps_incident, NONE);
	cr_expect_eq(ps->ps_limited, true);
	cr_expect_eq(ps->ps_ace, false);
	cr_expect_eq(ps->ps_tank, true);
	cr_expect_eq(ps->ps_puncture_proof, false);
	cr_expect_eq(ps->ps_prioritised, false);

	game_proc(ga, "playerstate 5 775 20 1 0 1 0 0");
	ps = &ga->ga_players[5];

	cr_expect_eq(ps->ps_id, 5);
	cr_expect_eq(ps->ps_dist, 775);
	cr_expect_eq(ps->ps_incident, NONE);
	cr_expect_eq(ps->ps_limited, true);
	cr_expect_eq(ps->ps_ace, false);
	cr_expect_eq(ps->ps_tank, true);
	cr_expect_eq(ps->ps_puncture_proof, false);
	cr_expect_eq(ps->ps_prioritised, false);
	ps = &ga->ga_players[4];
	cr_expect_eq(ps->ps_id, 5);
	cr_expect_eq(ps->ps_dist, 900);
	cr_expect_eq(ps->ps_incident, NONE);
	cr_expect_eq(ps->ps_limited, true);
	cr_expect_eq(ps->ps_ace, false);
	cr_expect_eq(ps->ps_tank, true);
	cr_expect_eq(ps->ps_puncture_proof, false);
	cr_expect_eq(ps->ps_prioritised, false);
	ps = &ga->ga_players[3];
	cr_expect_eq(ps->ps_id, 5);
	cr_expect_eq(ps->ps_dist, 800);
	cr_expect_eq(ps->ps_incident, NONE);
	cr_expect_eq(ps->ps_limited, true);
	cr_expect_eq(ps->ps_ace, false);
	cr_expect_eq(ps->ps_tank, true);
	cr_expect_eq(ps->ps_puncture_proof, false);
	cr_expect_eq(ps->ps_prioritised, false);
	ps = &ga->ga_players[2];
	cr_expect_eq(ps->ps_id, 94);
	cr_expect_eq(ps->ps_dist, 925);
	cr_expect_eq(ps->ps_incident, NONE);
	cr_expect_eq(ps->ps_limited, false);
	cr_expect_eq(ps->ps_ace, true);
	cr_expect_eq(ps->ps_tank, false);
	cr_expect_eq(ps->ps_puncture_proof, true);
	cr_expect_eq(ps->ps_prioritised, true);
	ps = &ga->ga_players[1];
	cr_expect_eq(ps->ps_id, 4);
	cr_expect_eq(ps->ps_dist, 450);
	cr_expect_eq(ps->ps_incident, HazCarCrash);
	cr_expect_eq(ps->ps_limited, false);
	cr_expect_eq(ps->ps_ace, false);
	cr_expect_eq(ps->ps_tank, false);
	cr_expect_eq(ps->ps_puncture_proof, true);
	cr_expect_eq(ps->ps_prioritised, true);
	ps = &ga->ga_players[0];
	cr_expect_eq(ps->ps_id, 7);
	cr_expect_eq(ps->ps_dist, 525);
	cr_expect_eq(ps->ps_incident, HazFlatTire);
	cr_expect_eq(ps->ps_limited, true);
	cr_expect_eq(ps->ps_ace, false);
	cr_expect_eq(ps->ps_tank, true);
	cr_expect_eq(ps->ps_puncture_proof, false);
	cr_expect_eq(ps->ps_prioritised, false);

	game_proc(ga, "lscards 7 15 16 13 0 9");

	cr_expect_eq(ga->ga_hand[0], DefSpareWheel);
	cr_expect_eq(ga->ga_hand[1], Dst50kms);
	cr_expect_eq(ga->ga_hand[2], Dst75kms);
	cr_expect_eq(ga->ga_hand[3], SpePrioritised);
	cr_expect_eq(ga->ga_hand[4], HazCarCrash);
	cr_expect_eq(ga->ga_hand[5], DefGreenLight);

	game_proc(ga, "playerstate 5 775 20 1 0 1 0 0");
	ps = &ga->ga_players[0];

	cr_expect_eq(ps->ps_id, 5);
	cr_expect_eq(ps->ps_dist, 775);
	cr_expect_eq(ps->ps_incident, NONE);
	cr_expect_eq(ps->ps_limited, true);
	cr_expect_eq(ps->ps_ace, false);
	cr_expect_eq(ps->ps_tank, true);
	cr_expect_eq(ps->ps_puncture_proof, false);
	cr_expect_eq(ps->ps_prioritised, false);
	game_proc(ga, "playerstate 5 800 20 1 0 1 0 0 toto");
	game_proc(ga, "playerstate 5 800 20 1 0 1 0 0");
	ps = &ga->ga_players[1];

	cr_expect_eq(ps->ps_id, 5);
	cr_expect_eq(ps->ps_dist, 800);
	cr_expect_eq(ps->ps_incident, NONE);
	cr_expect_eq(ps->ps_limited, true);
	cr_expect_eq(ps->ps_ace, false);
	cr_expect_eq(ps->ps_tank, true);
	cr_expect_eq(ps->ps_puncture_proof, false);
	cr_expect_eq(ps->ps_prioritised, false);
	game_delete(ga);
}
