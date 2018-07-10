/*
** COBRA CODING CLUB PROJECT
** server
** File description:
** Selector
*/

#ifndef SELECTOR_HPP_
#define SELECTOR_HPP_

#include <list>
#include <memory>
#include <sys/select.h>
#include "hdl/IHandle.hpp"

namespace io {

constexpr auto SELECTOR_BACKLOG(30);

class Selector {
public:
	Selector();
	Selector(const Selector &) = delete;
	~Selector();

	virtual void registerHandle(std::unique_ptr<hdl::IHandle> &hdl)
	{
		_handles.push_back(std::move(hdl));
	}
	virtual bool run()
	{
		if (_live) {
			_setFileDescriptors();
			_select();
			_readOnActiveHandles();
		}
		return (_live);
	}
	virtual void loop()
	{
		while (run())
			;
	}
	virtual void setLive(bool status) noexcept { _live = status; }

	const unsigned int id;
	static std::list<Selector *> launchedSelectors;

protected:
	void _select();
	void _setFileDescriptors() noexcept;
	void _readOnActiveHandles();
	static void __uponsignal(int signum);

	std::list<std::unique_ptr<hdl::IHandle>> _handles;
	static unsigned int __nextId;
	bool _live;
	int _highestSetFd;
	fd_set _fdSet;
};

} // namespace io

#endif /* !SELECTOR_HPP_ */
