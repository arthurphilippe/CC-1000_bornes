/*
** COBRA CODING CLUB PROJECT
** server
** File description:
** IHandle
*/

#ifndef IHANDLE_HPP_
#define IHANDLE_HPP_

#include <functional>
#include "io/hdl/IMsgProcessor.hpp"

namespace io {
class Selector;
}

namespace io::hdl {

enum class HType {
	PORT,
	CLIENT,
	PLAYER,
	SERVER,
	STDIN,
};

class IHandle {
public:
	virtual ~IHandle() = default;
	virtual HType getType() const noexcept = 0;
	virtual int getFd() const noexcept = 0;
	virtual void onCycle() = 0;
	virtual void onRead() = 0;
	virtual bool live() const noexcept = 0;
};

// using MsgProcessor =
// 	std::function<void(IHandle &hdl, const std::string &msg)>;

} // namespace io::hdl

#endif /* !IHANDLE_HPP_ */
