/*
** COBRA CODING CLUB PROJECT
** server
** File description:
** main
*/

#include <iostream>
#include "game/Manager.hpp"
#include "io/Selector.hpp"
#include "io/hdl/Listener.hpp"

int main()
{
	game::Manager stor;
	std::unique_ptr<io::hdl::IHandle> listener(
		new io::hdl::Listener(stor, 4242));
	stor.registerHandle(listener);
	stor.loop();
	std::cout << "Hello Jafar" << std::endl;
}
