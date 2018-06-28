/*
** EPITECH PROJECT, 2018
** server
** File description:
** Listener
*/

#include <arpa/inet.h>
#include <exception>
#include <iostream>
#include <stdexcept>

#include "Listener.hpp"
#include "net/Selector.hpp"

namespace sys {

#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

} // namespace sys

namespace net::hdl {

Listener::Listener(Selector &stor, int port)
	: _stor(stor), _sock(socket(PF_INET, SOCK_STREAM, 0)), _live(true)
{
	if (!_sock || _sock == -1 || portBind(_sock, port) == -1 ||
		listen(_sock, SELECTOR_BACKLOG) == -1) {
		sys::close(_sock);
		throw std::runtime_error(sys::strerror(errno));
	}
}

Listener::~Listener()
{
	shutdown(_sock, SHUT_RDWR);
	sys::close(_sock);
}

int Listener::portBind(int sock, int port)
{
	struct sockaddr_in sin;

	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = INADDR_ANY;
	return (bind(sock, (struct sockaddr *) &sin, sizeof(sin)));
}

} // namespace net::hdl
