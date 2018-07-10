/*
** EPITECH PROJECT, 2018
** client
** File description:
** game
*/

#include "game.h"
#include <criterion/assert.h>
#include <criterion/criterion.h>

Test(Game, Create)
{
	game_t *ga = game_create();

	cr_assert(ga);
	for (unsigned int i = 0; i < 6; i += 1)
		cr_expect_eq(ga->ga_hand[i], NONE);
	cr_expect_eq(ga->ga_player_nb, 0);
	cr_expect_eq(ga->ga_id, 0);
	game_delete(ga);
}

Test(Game, Connection)
{
	game_t *ga = game_create();

	cr_assert(ga);
	cr_expect_neq(game_connect(ga, "google.fr:443"), -1);
	cr_expect_neq(ga->ga_socketfd, -1);
	cr_expect_eq(ga->ga_live, true);
}

Test(Game, ConnectionError1)
{
	game_t *ga = game_create();

	cr_assert(ga);
	cr_expect_eq(game_connect(ga, "google.fr"), -1);
	cr_expect_eq(ga->ga_socketfd, -1);
	cr_expect_eq(ga->ga_live, false);
}

Test(Game, ConnectionError2)
{
	game_t *ga = game_create();

	cr_assert(ga);
	cr_expect_eq(game_connect(ga, "google.fr:0"), -1);
	cr_expect_eq(ga->ga_socketfd, -1);
	cr_expect_eq(ga->ga_live, false);
}

Test(Game, ConnectionError3)
{
	game_t *ga = game_create();

	cr_assert(ga);
	cr_expect_eq(game_connect(ga, "google.zorg:443"), -1);
	cr_expect_eq(ga->ga_socketfd, -1);
	cr_expect_eq(ga->ga_live, false);
}
