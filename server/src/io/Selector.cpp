/*
** COBRA CODING CLUB PROJECT
** server
** File description:
** Selector
*/

#include "Selector.hpp"
#include <csignal>
#include <stdexcept>
#include <string.h>

namespace io {

std::list<Selector *> Selector::launchedSelectors;
unsigned int Selector::__nextId(1);

Selector::Selector() : id(__nextId++), _live(true)
{
	std::signal(SIGINT, __uponsignal);
	launchedSelectors.push_back(this);
}

Selector::~Selector()
{
	for (auto it(launchedSelectors.begin());
		it != launchedSelectors.end(); std::advance(it, 1)) {
		if ((*it)->id == this->id) it = launchedSelectors.erase(it);
		if (it == launchedSelectors.end()) break;
	}
}

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

void Selector::__uponsignal(int signum)
{
	(void) signum;
	for (auto &it : launchedSelectors) {
		it->setLive(false);
	}
}

} // namespace io
