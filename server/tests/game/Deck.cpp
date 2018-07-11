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
	cr_log_warn("this test will most likely fail");
	game::Deck deck;
	const auto &cards = deck.getCards();

	unsigned int countRedLight(0);
	unsigned int count75kms(0);

	cr_expect_eq(cards.size(), 106);

	for (const auto &card : cards) {
		cr_log_info("card type: %d", static_cast<unsigned int>(card));
		if (card == game::Card::HazRedLight) countRedLight += 1;
		if (card == game::Card::Dst75kms) count75kms += 1;
	}
	cr_expect_eq(countRedLight, 5);
	cr_expect_eq(count75kms, 10);
}

Test(Deck, 2_drawCard)
{
	cr_log_warn("this test will most likely fail");
	game::Deck deck;
	const auto &cards = deck.getCards();

	unsigned int countRedLight(0);
	unsigned int count75kms(0);

	cr_expect_eq(cards.size(), 106);

	while (!cards.empty()) {
		auto card = deck.drawCard();
		cr_log_info("card type: %d", static_cast<unsigned int>(card));
		if (card == game::Card::HazRedLight) countRedLight += 1;
		if (card == game::Card::Dst75kms) count75kms += 1;
	}
	cr_expect_eq(countRedLight, 5);
	cr_expect_eq(count75kms, 10);
	deck.throwAway(game::Card::DefRepair);
	cr_expect_eq(cards.size(), 1);

	cr_expect_eq(deck.drawCard(), game::Card::DefRepair);
}
