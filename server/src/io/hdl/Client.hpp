/*
** EPITECH PROJECT, 2018
** server
** File description:
** Client
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <list>
#include <string>
#include "io/hdl/IHandle.hpp"

namespace io::hdl {

class Client : public IHandle {
public:
	Client(Selector &stor, int fd) : _stor(stor), _fd(fd), _live(true) {}
	~Client() {}

	virtual HType getType() const noexcept override
	{
		return HType::CLIENT;
	}
	virtual int getFd() const noexcept override { return _fd; }
	virtual void onCycle() override {}
	virtual void onRead() override;
	virtual bool live() const noexcept override { return _live; }

protected:
	Selector &_stor;
	int _fd;
	bool _live;
	std::list<std::string> _receivedMsgs;
};

} // namespace io::hdl

#endif /* !CLIENT_HPP_ */
