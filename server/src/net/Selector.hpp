/*
** EPITECH PROJECT, 2018
** server
** File description:
** Selector
*/

#ifndef SELECTOR_HPP_
#define SELECTOR_HPP_

#include <list>
#include <memory>
#include <sys/select.h>
#include "hdl/IHandle.hpp"

namespace net {

constexpr auto SELECTOR_BACKLOG(30);

class Selector {
public:
	Selector();
	Selector(const Selector &) = delete;
	~Selector();

	void addHandle(std::unique_ptr<hdl::IHandle> &hdl)
	{
		_handles.push_back(std::move(hdl));
	}
	bool run()
	{
		if (_live) {
			_setFileDescriptors();
			_select();
			_readOnActiveHandles();
		}
		return (_live);
	}
	void loop()
	{
		while (run())
			;
	}
	void setLive(bool status) { _live = status; }

private:
	void _select();
	void _setFileDescriptors() noexcept;
	void _readOnActiveHandles();
	std::list<std::unique_ptr<hdl::IHandle>> _handles;

	bool _live;
	int _highestSetFd;
	fd_set _fdSet;
};

} // namespace net

#endif /* !SELECTOR_HPP_ */
