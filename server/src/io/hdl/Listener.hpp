/*
** COBRA CODING CLUB PROJECT
** server
** File description:
** listener
*/

#ifndef LISTENER_HPP_
#define LISTENER_HPP_

#include "IHandle.hpp"

namespace io::hdl {

class Listener : public IHandle {
public:
	Listener(Selector &stor, int port);
	~Listener();

	HType getType() const noexcept override { return HType::PORT; }
	int getFd() const noexcept override { return _fd; }
	void onCycle() override {}
	void onRead() override;
	bool live() const noexcept override { return _live; }

	static int portBind(int sock, int port);

private:
	Selector &_stor;
	int _fd;
	bool _live;
};

} // namespace io::hdl

#endif /* !LISTENER_HPP_ */
