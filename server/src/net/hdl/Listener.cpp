/*
** EPITECH PROJECT, 2018
** server
** File description:
** Listener
*/

#include "Listener.hpp"
#include <arpa/inet.h>
#include <exception>
#include <stdexcept>

namespace sys {

#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

} // namespace sys

namespace net::hdl {

Listener::Listener(int port)
	: _sock(socket(PF_INET, SOCK_STREAM, 0)), _live(true)
{
	if (_sock == -1 || portBind(_sock, port) ||
		listen(_sock, SELECTOR_BACKLOG) == -1) {
		sys::close(_sock);
		throw std::runtime_error(sys::strerror(errno));
	}
}

Listener::~Listener()
{}

int Listener::portBind(int sock, int port)
{
	struct sockaddr_in sin;

	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = INADDR_ANY;
	return (bind(sock, (struct sockaddr *) &sin, sizeof(sin)));
}

} // namespace net::hdl
