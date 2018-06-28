/*
** EPITECH PROJECT, 2018
** server
** File description:
** Selector
*/

#ifndef SELECTOR_HPP_
#define SELECTOR_HPP_

#include <list>
#include <memory>
#include "hdl/IHandle.hpp"

namespace net {

class Selector {
public:
	Selector();
	~Selector();

	void addHandle(std::unique_ptr<hdl::IHandle> &hdl)
	{
		_handles.push_back(std::move(hdl));
	}

private:
	std::list<std::unique_ptr<hdl::IHandle>> _handles;
};

} // namespace net

#endif /* !SELECTOR_HPP_ */
