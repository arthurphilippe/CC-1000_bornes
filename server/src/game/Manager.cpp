/*
** EPITECH PROJECT, 2018
** server
** File description:
** Manager
*/

#include "Manager.hpp"

namespace game {

Manager::Manager() : Selector() {}

Manager::~Manager() {}

void Manager::registerHandle(std::unique_ptr<io::hdl::Client> &hdl)
{
	// _despatch.push_back(std::move(hdl));
	auto found(false);
	for (auto it = _waitingGames.begin();
		it != _waitingGames.end() && !found; std::next(it)) {
		if (!(*it)->full()) {
			(*it)->processMsg(*hdl, "");
			found = true;
		}
	}
	if (!found) {
		auto *nGame = new MilleBornes;
		if (!nGame) throw std::runtime_error("Out of memory");
		_waitingGames.emplace_back(nGame);
		_waitingGames.back()->processMsg(*hdl, "");
	}
	io::hdl::IHandle *interfacedHdl = hdl.release();
	_handles.emplace_back(interfacedHdl);
}
} // namespace game
