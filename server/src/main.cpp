/*
** EPITECH PROJECT, 2018
** server
** File description:
** main
*/

#include <iostream>
#include "net/Selector.hpp"
#include "net/hdl/Listener.hpp"

int main()
{
	net::Selector stor;
	std::unique_ptr<net::hdl::IHandle> listener(
		new net::hdl::Listener(stor, 4242));
	stor.addHandle(listener);
	stor.loop();
	std::cout << "Hello Jafar" << std::endl;
}
