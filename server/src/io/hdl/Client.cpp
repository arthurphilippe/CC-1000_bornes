/*
** COBRA CODING CLUB PROJECT
** server
** File description:
** Client
*/

#include "Client.hpp"
#include <unistd.h>
#include "io/Selector.hpp"
#include "tools/Parsing.hpp"

namespace io::hdl {

Client::~Client() { close(_fd); }

void Client::onCycle()
{
	while (!_receivedMsgs.empty()) {
		if (_receivedMsgs.front() == "quit") _stor.setLive(false);
		if (_msgProcessor && !_msgProcessor->live())
			_msgProcessor.reset();
		dprintf(_fd, "echo: %s\n", _receivedMsgs.front().c_str());
		if (_msgProcessor && _msgProcessor->live())
			_msgProcessor->processMsg(
				*this, _receivedMsgs.front());
		_receivedMsgs.pop_front();
	}
}

void Client::onRead()
{
	char buff[513];
	int r = read(this->_fd, buff, 512);
	buff[r] = 0;
	tools::Parsing::fillList(_receivedMsgs, buff, "\n\r");
}

} // namespace io::hdl
