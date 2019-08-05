/*
** COBRA CODING CLUB PROJECT
** server
** File description:
** Client
*/

#include "Client.hpp"
#include <iostream>
#include <unistd.h>
#include "io/Selector.hpp"
#include "tools/Parsing.hpp"

namespace io::hdl {

unsigned long Client::__id(1);

Client::~Client() { close(_fd); }

void Client::onCycle()
{
	if (_eof) _live = false;
	while (!_receivedMsgs.empty()) {
		if (_msgProcessor && !_msgProcessor->live())
			_msgProcessor.reset();
		if (_msgProcessor && _msgProcessor->live())
			_msgProcessor->processMsg(
				*this, _receivedMsgs.front());
		if (!_msgProcessor) {
			if (_receivedMsgs.front() == "quit") _live = false;
			this->stream() << _receivedMsgs.front() << std::endl;
			this->dumpStream();
		}
		_receivedMsgs.pop_front();
	}
}

void Client::onRead()
{
	char buff[513];
	int r = read(this->_fd, buff, 512);
	if (r > 0) {
		buff[r] = 0;
		tools::Parsing::fillList(_receivedMsgs, buff, "\n\r");
	} else {
		std::cout << "quit" << std::endl;
		_receivedMsgs.push_front("quit");
		_eof = true;
	}
}

} // namespace io::hdl
