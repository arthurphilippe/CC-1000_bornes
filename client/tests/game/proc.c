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
}
