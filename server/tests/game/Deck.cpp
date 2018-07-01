/*
** COBRA CODING CLUB PROJECT
** server
** File description:
** Deck
*/

#include "game/Deck.hpp"
#include <criterion/assert.h>
#include <criterion/criterion.h>

Test(Deck, 1_cards)
{
	game::Deck deck;
	const auto &cards = deck.getCards();

	unsigned int countRedLight(0);
	unsigned int count75kms(0);

	for (const auto &card : cards) {
		if (card == game::Card::AttRedLight) countRedLight += 1;
		if (card == game::Card::Dst75kms) count75kms += 1;
	}
	cr_expect_eq(countRedLight, 5);
	cr_expect_eq(count75kms, 10);
}
