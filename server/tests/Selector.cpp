/*
** EPITECH PROJECT, 2018
** server
** File description:
** Selector
*/

#include "io/Selector.hpp"
#include <criterion/assert.h>
#include <criterion/criterion.h>
#include "io/hdl/IHandle.hpp"
#include "unistd.h"

namespace io::hdl {

class PipeHandle : public IHandle {
public:
	PipeHandle(io::Selector &stor) : _stor(stor), _live(true)
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

	io::Selector &_stor;
	bool _live;
	int _filedes[2];
};

} // namespace io::hdl

Test(Selector, 1_basic, .timeout = 2)
{
	io::Selector stor;
	auto *dumbhdl = new io::hdl::PipeHandle(stor);
	std::unique_ptr<io::hdl::IHandle> hdl(dumbhdl);

	cr_assert(dumbhdl);
	stor.registerHandle(hdl);
	dprintf(dumbhdl->_filedes[1], "hi\n");

	cr_assert_eq(stor.run(), true);
	dprintf(dumbhdl->_filedes[1], "quit\n");
	cr_assert_eq(stor.run(), false);
}

Test(Selector, 2_invalid_fd, .timeout = 2)
{
	io::Selector stor;
	auto *dumbhdl = new io::hdl::PipeHandle(stor);
	std::unique_ptr<io::hdl::IHandle> hdl(dumbhdl);

	cr_assert(dumbhdl);
	stor.registerHandle(hdl);

	dumbhdl->_filedes[0] = -1;
	cr_assert_throw(stor.run(), std::runtime_error);
}
