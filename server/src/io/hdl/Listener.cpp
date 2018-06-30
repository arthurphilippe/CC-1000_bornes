/*
** EPITECH PROJECT, 2018
** server
** File description:
** Listener
*/

#include "Listener.hpp"
#include <arpa/inet.h>
#include <errno.h>
#include <exception>
#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <system_error>
#include <unistd.h>
#include "io/Selector.hpp"
#include "io/hdl/Client.hpp"

namespace io::hdl {

Listener::Listener(Selector &stor, int port)
	: _stor(stor), _fd(socket(PF_INET, SOCK_STREAM, 0)), _live(true)
{
	if (!_fd || _fd == -1 || portBind(_fd, port) == -1 ||
		listen(_fd, SELECTOR_BACKLOG) == -1) {
		close(_fd);
		throw std::runtime_error(strerror(errno));
	}
}

Listener::~Listener()
{
	shutdown(_fd, SHUT_RDWR);
	close(_fd);
}

void Listener::onRead()
{
	int socket;
	struct sockaddr_in sin;
	socklen_t sin_len = sizeof(sin);

	socket = accept(_fd, (struct sockaddr *) &sin, &sin_len);
	if (socket == -1) throw std::runtime_error(strerror(errno));
	dprintf(socket, "%s\n", "Welcome");
	std::unique_ptr<IHandle> tmpHdl(new io::hdl::Client(_stor, socket));
	if (!tmpHdl) close(socket);
	_stor.registerHandle(tmpHdl);
}

int Listener::portBind(int sock, int port)
{
	struct sockaddr_in sin;

	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = INADDR_ANY;
	return (bind(sock, (struct sockaddr *) &sin, sizeof(sin)));
}

} // namespace io::hdl
