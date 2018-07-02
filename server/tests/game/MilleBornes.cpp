/*
** EPITECH PROJECT, 2018
** server
** File description:
** MilleBornes
*/

#include "game/MilleBornes.hpp"
#include <criterion/assert.h>
#include <criterion/criterion.h>
#include <unistd.h>
#include "io/Selector.hpp"
#include "io/hdl/Client.hpp"

class DumbClient : public io::hdl::Client {
public:
	DumbClient(io::Selector &stor, int fd) : Client(stor, fd) {}
	DumbClient(io::Selector &stor,
		std::shared_ptr<io::hdl::IMsgProcessor> &proc, int fd)
		: Client(stor, proc, fd)
	{}
	std::list<std::string> &getMsgs() { return _receivedMsgs; }
	void setFd(int fd) { _fd = fd; }
};

Test(MilleBornes, registration)
{
	io::Selector stor;
	int filedes[2];

	if (pipe(filedes) == -1) cr_assert_fail("failed to pipe: errno %d");
	auto *game = new game::MilleBornes;
	std::shared_ptr<io::hdl::IMsgProcessor> proc(game);
	DumbClient clienta(stor, proc, filedes[0]);
	DumbClient clientb(stor, proc, filedes[0]);

	dprintf(filedes[1], "Hi\n");
	clienta.onRead();
	dprintf(filedes[1], "Hi\n");
	clientb.onRead();
	clienta.onCycle();
	clientb.onCycle();
	dprintf(filedes[1], "Hi\n");
	clientb.onRead();
	clientb.onCycle();
	dprintf(filedes[1], "Hi\n");
	clientb.onRead();
	clientb.onCycle();
	dprintf(filedes[1], "Hi\n");
	clientb.onRead();
	clientb.onCycle();
	dprintf(filedes[1], "Hi\n");
	clientb.onRead();
	clientb.onCycle();
	dprintf(filedes[1], "Hi\n");
	clientb.onRead();
	clientb.onCycle();
	dprintf(filedes[1], "Hi\n");
	clientb.onRead();
	clientb.onCycle();

	cr_assert_eq(game->ready(), true);
	cr_assert_eq(game->full(), false);
	close(filedes[1]);
}

Test(MilleBornes, useDist)
{
	io::Selector stor;
	int filedes[2];

	if (pipe(filedes) == -1) cr_assert_fail("failed to pipe: errno %d");
	auto *game = new game::MilleBornes;
	std::shared_ptr<io::hdl::IMsgProcessor> proc(game);
	DumbClient client(stor, proc, filedes[0]);

	game::MilleBornes::Player pl{
		{}, client, 0, game::Card::NONE, false, false};
	game::Card card = game::Card::Dst75kms;
	cr_expect_not(game->useCard(pl, card));
	cr_expect_eq(pl.distance, 0);
	cr_expect_neq(card, game::Card::NONE);
	cr_expect_not(game->useCard(pl, card));
	cr_expect_eq(pl.distance, 0);

	pl.light = true;
	cr_expect(game->useCard(pl, card));
	cr_expect_eq(pl.distance, 75);
	cr_expect_eq(card, game::Card::NONE);

	card = game::Card::Dst25kms;
	cr_expect(game->useCard(pl, card));
	cr_expect_eq(pl.distance, 100);
	cr_expect_eq(card, game::Card::NONE);

	card = game::Card::Dst50kms;
	cr_expect(game->useCard(pl, card));
	cr_expect_eq(pl.distance, 150);
	cr_expect_eq(card, game::Card::NONE);

	card = game::Card::Dst100kms;
	cr_expect(game->useCard(pl, card));
	cr_expect_eq(pl.distance, 250);
	cr_expect_eq(card, game::Card::NONE);

	card = game::Card::Dst200kms;
	cr_expect(game->useCard(pl, card));
	cr_expect_eq(pl.distance, 450);
	cr_expect_eq(card, game::Card::NONE);

	card = game::Card::HazCarCrash;
	cr_expect_not(game->useCard(pl, card));
	cr_expect_eq(pl.distance, 450);
	cr_expect_neq(card, game::Card::NONE);

	card = game::Card::Dst200kms;
	cr_expect(game->useCard(pl, card));
	cr_expect_eq(pl.distance, 650);
	cr_expect_eq(card, game::Card::NONE);

	card = game::Card::Dst200kms;
	cr_expect(game->useCard(pl, card));
	cr_expect_eq(pl.distance, 850);
	cr_expect_eq(card, game::Card::NONE);

	card = game::Card::Dst200kms;
	cr_expect_not(game->useCard(pl, card));
	cr_expect_eq(pl.distance, 850);
	cr_expect_neq(card, game::Card::NONE);
}

Test(MilleBornes, useDef)
{
	io::Selector stor;
	int filedes[2];

	if (pipe(filedes) == -1) cr_assert_fail("failed to pipe: errno %d");
	auto *game = new game::MilleBornes;
	std::shared_ptr<io::hdl::IMsgProcessor> proc(game);
	DumbClient client(stor, proc, filedes[0]);

	game::MilleBornes::Player pl{
		{}, client, 0, game::Card::HazFlatTire, false, false};

	auto card = game::Card::DefGas;
	cr_expect_not(game->useCard(pl, card));
	cr_expect_eq(pl.hazard, game::Card::HazFlatTire,
		"hazard is %d instead of %d", pl.hazard,
		game::Card::HazFlatTire);
	cr_expect_neq(card, game::Card::NONE);

	card = game::Card::DefSpareWheel;
	cr_expect(game->useCard(pl, card));
	cr_expect_eq(pl.hazard, game::Card::NONE,
		"hazard is %d instead of %d", pl.hazard, game::Card::NONE);
	cr_expect_eq(card, game::Card::NONE);

	card = game::Card::DefSpareWheel;
	cr_expect_not(game->useCard(pl, card));
	cr_expect_eq(pl.hazard, game::Card::NONE,
		"hazard is %d instead of %d", pl.hazard, game::Card::NONE);
	cr_expect_neq(card, game::Card::NONE);
}
