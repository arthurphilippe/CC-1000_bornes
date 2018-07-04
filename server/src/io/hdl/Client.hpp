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
#include <sstream>
#include <string>
#include "io/hdl/IHandle.hpp"
#include "io/hdl/IMsgProcessor.hpp"

namespace io::hdl {

class Client : public IHandle {
public:
	Client(Selector &stor, int fd)
		: id(__id++),
		  _stor(stor),
		  _msgProcessor(nullptr),
		  _fd(fd),
		  _live(true)
	{}
	Client(Selector &stor, std::shared_ptr<IMsgProcessor> &proc, int fd)
		: id(__id++),
		  _stor(stor),
		  _msgProcessor(proc),
		  _fd(fd),
		  _live(true)
	{}

	~Client();

	virtual HType getType() const noexcept override
	{
		return HType::CLIENT;
	}
	virtual int getFd() const noexcept override { return _fd; }
	virtual void onCycle() override;
	virtual void onRead() override;
	virtual bool live() const noexcept override { return _live; }
	virtual void setLive(bool live) noexcept override { _live = live; }
	void setMsgProcessor(std::shared_ptr<IMsgProcessor> &proc)
	{
		_msgProcessor = proc;
	}
	virtual std::ostream &stream() noexcept { return _oss; }
	virtual void dumpStream()
	{
		if (!_oss.str().empty() && _live) {
			dprintf(_fd, "%s", _oss.str().c_str());
			_oss.str() = "";
		}
	}

	const unsigned long id;

protected:
	Selector &_stor;
	std::shared_ptr<IMsgProcessor> _msgProcessor;
	int _fd;
	bool _live;
	std::list<std::string> _receivedMsgs;

	std::ostringstream _oss;

	static unsigned long __id;
};

} // namespace io::hdl

#endif /* !CLIENT_HPP_ */
