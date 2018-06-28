/*
** EPITECH PROJECT, 2018
** server
** File description:
** main
*/

#include <iostream>
#include "net/hdl/Listener.hpp"

int main()
{
	net::hdl::Listener listener(4242);
	std::cout << "Hello Jafar" << std::endl;
}
