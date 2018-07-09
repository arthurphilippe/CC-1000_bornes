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

int main(int ac, char **av)
{
	auto ret(0);
	if (ac >= 2) {
		try {
			auto portnb(std::stoi(av[1]));
			game::Manager stor;
			std::unique_ptr<io::hdl::IHandle> listener(
				new io::hdl::Listener(stor, portnb));
			stor.registerHandle(listener);
			stor.loop();
		} catch (std::exception &e) {
			e.what();
			ret = 1;
		}
	} else {
		std::cerr << av[0] << ": please provide a port number"
			  << std::endl;
		ret = 1;
	}
	return ret;
}
