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
}
