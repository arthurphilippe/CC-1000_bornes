/*
** EPITECH PROJECT, 2018
** server
** File description:
** listener
*/

#ifndef LISTENER_HPP_
#define LISTENER_HPP_

#include "IHandle.hpp"

namespace net::hdl {

constexpr auto SELECTOR_BACKLOG(30);

class Listener : public IHandle {
public:
	Listener(Selector &stor, int port);
	~Listener();

	HType getType() const noexcept override
	{
		return HType::PORT;
	}
	int getFd() const noexcept override
	{
		return _fd;
	}
	void onCycle() override
	{}
	void onRead() override;
	bool live() const noexcept override
	{
		return _live;
	}

	static int portBind(int sock, int port);

private:
	Selector &_stor;
	int _fd;
	bool _live;
};

} // namespace net::hdl

#endif /* !LISTENER_HPP_ */
