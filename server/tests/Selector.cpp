/*
** EPITECH PROJECT, 2018
** server
** File description:
** Selector
*/

#include "net/Selector.hpp"
#include <criterion/assert.h>
#include <criterion/criterion.h>
#include "net/hdl/IHandle.hpp"
#include "unistd.h"

namespace net::hdl {

class PipeHandle : public IHandle {
public:
	PipeHandle(net::Selector &stor) : _stor(stor), _live(true)
	{
		if (pipe(_filedes) == -1)
			throw std::runtime_error(strerror(errno));
	}
	~PipeHandle()
	{
		close(_filedes[0]);
		close(_filedes[1]);
	}

	HType getType() const noexcept override { return HType::STDIN; }
	int getFd() const noexcept override { return (_filedes[0]); }
	void onCycle() override {}
	void onRead() override
	{
		char buf[513];
		int r = read(_filedes[0], buf, 512);

		buf[r] = 0;
		std::string str(buf);
		if (str == "quit\n") _stor.setLive(false);
	}
	bool live() const noexcept override { return _live; }

	net::Selector &_stor;
	bool _live;
	int _filedes[2];
};

} // namespace net::hdl

Test(Selector, 1_basic, .timeout = 2)
{
	net::Selector stor;
	auto *dumbhdl = new net::hdl::PipeHandle(stor);
	std::unique_ptr<net::hdl::IHandle> hdl(dumbhdl);

	cr_assert(dumbhdl);
	stor.addHandle(hdl);
	dprintf(dumbhdl->_filedes[1], "hi\n");

	cr_assert_eq(stor.run(), true);
	dprintf(dumbhdl->_filedes[1], "quit\n");
	cr_assert_eq(stor.run(), false);
}

Test(Selector, 2_invalid_fd, .timeout = 2)
{
	net::Selector stor;
	auto *dumbhdl = new net::hdl::PipeHandle(stor);
	std::unique_ptr<net::hdl::IHandle> hdl(dumbhdl);

	cr_assert(dumbhdl);
	stor.addHandle(hdl);

	dumbhdl->_filedes[0] = -1;
	cr_assert_throw(stor.run(), std::runtime_error);
}
