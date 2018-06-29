/*
** EPITECH PROJECT, 2018
** server
** File description:
** IHandle
*/

#ifndef IHANDLE_HPP_
#define IHANDLE_HPP_

namespace net {
class Selector;
}

namespace net::hdl {

enum class HType {
	PORT,
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

} // namespace net::hdl

#endif /* !IHANDLE_HPP_ */
