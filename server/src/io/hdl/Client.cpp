/*
** EPITECH PROJECT, 2018
** server
** File description:
** Client
*/

#include "Client.hpp"
#include "unistd.h"

namespace io::hdl {

void Client::onRead()
{
	char buff[513];
	int r = read(this->_fd, buff, 512);
}

} // namespace io::hdl
