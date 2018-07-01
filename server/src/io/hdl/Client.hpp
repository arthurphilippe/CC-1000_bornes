/*
** COBRA CODING CLUB PROJECT
** server
** File description:
** Client
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <list>
#include <memory>
#include <string>
#include "io/hdl/IHandle.hpp"
#include "io/hdl/IMsgProcessor.hpp"

namespace io::hdl {

class Client : public IHandle {
public:
	Client(Selector &stor, int fd) : _stor(stor), _fd(fd), _live(true) {}
	~Client();

	virtual HType getType() const noexcept override
	{
		return HType::CLIENT;
	}
	virtual int getFd() const noexcept override { return _fd; }
	virtual void onCycle() override;
	virtual void onRead() override;
	virtual bool live() const noexcept override { return _live; }
	void setMsgProcessor(std::shared_ptr<IMsgProcessor> &proc)
	{
		_msgProcessor = proc;
	}

protected:
	Selector &_stor;
	std::shared_ptr<IMsgProcessor> _msgProcessor;
	int _fd;
	bool _live;
	std::list<std::string> _receivedMsgs;
};

} // namespace io::hdl

#endif /* !CLIENT_HPP_ */
