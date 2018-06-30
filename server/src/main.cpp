/*
** EPITECH PROJECT, 2018
** server
** File description:
** main
*/

#include <iostream>
#include "io/Selector.hpp"
#include "io/hdl/Listener.hpp"

int main()
{
	io::Selector stor;
	std::unique_ptr<io::hdl::IHandle> listener(
		new io::hdl::Listener(stor, 4242));
	stor.registerHandle(listener);
	stor.loop();
	std::cout << "Hello Jafar" << std::endl;
}
