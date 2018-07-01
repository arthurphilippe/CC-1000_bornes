/*
** EPITECH PROJECT, 2018
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
		dprintf(_fd, "echo: %s\n", _receivedMsgs.front().c_str());
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
