/*
** EPITECH PROJECT, 2018
** server
** File description:
** Client
*/

#include "io/hdl/Client.hpp"
#include <criterion/assert.h>
#include <criterion/criterion.h>
#include <unistd.h>
#include "io/Selector.hpp"

class DumbClient : public io::hdl::Client {
public:
	DumbClient(io::Selector &stor, int fd) : Client(stor, fd) {}
	std::list<std::string> &getMsgs() { return _receivedMsgs; }
	void setFd(int fd) { _fd = fd; }
};

Test(ioHdlClient, 1_rcvdMsgs)
{
	io::Selector stor;
	int filedes[2];

	if (pipe(filedes) == -1) cr_assert_fail("failed to pipe: errno %d");
	DumbClient client(stor, filedes[0]);

	dprintf(filedes[1], "%s",
		"kappa\n\rwa\nkawaaaaaaaaaaaaaaaaaaaaaaiiiiiiiiiiiiiiiii\n"
		"\n");

	client.onRead();
	auto &msgs = client.getMsgs();

	cr_expect_eq(msgs.size(), 3);
	cr_expect_eq(msgs.front(), "kappa");
	msgs.pop_front();
	cr_assert_neq(msgs.empty(), true);
	cr_expect_eq(msgs.front(), "wa");
	msgs.pop_front();
	cr_assert_neq(msgs.empty(), true);
	cr_expect_eq(
		msgs.front(), "kawaaaaaaaaaaaaaaaaaaaaaaiiiiiiiiiiiiiiiii");
	msgs.pop_front();

	cr_assert_eq(msgs.empty(), true);

	close(filedes[1]);
}

Test(ioHdlClient, 2_getters)
{
	io::Selector stor;
	int filedes[2];

	if (pipe(filedes) == -1) cr_assert_fail("failed to pipe: errno %d");
	DumbClient client(stor, filedes[0]);

	cr_assert_eq(client.getFd(), filedes[0]);
	cr_assert_eq(client.live(), true);
	cr_assert_eq(client.getType(), io::hdl::HType::CLIENT);

	dprintf(filedes[1], "%s",
		"kappa\n\rwa\nkawaaaaaaaaaaaaaaaaaaaaaaiiiiiiiiiiiiiiiii\n"
		"\n");

	client.onRead();

	client.setFd(filedes[1]);
	client.onCycle();
	close(filedes[0]);
}
