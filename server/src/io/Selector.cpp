/*
** COBRA CODING CLUB PROJECT
** server
** File description:
** Selector
*/

#include "Selector.hpp"
#include <stdexcept>
#include <string.h>

namespace io {

Selector::Selector() : _live(true) {}

Selector::~Selector() {}

void Selector::_select()
{
	struct timeval tv {
		0, 1000
	};

	if (select(_highestSetFd + 1, &_fdSet, NULL, NULL, &tv) == -1) {
		throw std::runtime_error(strerror(errno));
	}
}

void Selector::_setFileDescriptors() noexcept
{
	_highestSetFd = 0;
	FD_ZERO(&_fdSet);
	for (auto &it : _handles) {
		auto fd = it->getFd();
		FD_SET(fd, &_fdSet);
		if (_highestSetFd < fd) _highestSetFd = fd;
	}
}

void Selector::_readOnActiveHandles()
{
	for (auto it = _handles.begin(); it != _handles.end();
		std::advance(it, 1)) {
		if (FD_ISSET((*it)->getFd(), &_fdSet)) (*it)->onRead();
		if (!(*it)->live()) it = _handles.erase(it);
		if (it == _handles.end()) break;
		(*it)->onCycle();
	}
}

} // namespace io
