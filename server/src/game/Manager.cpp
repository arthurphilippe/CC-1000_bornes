/*
** EPITECH PROJECT, 2018
** server
** File description:
** Manager
*/

#include "Manager.hpp"

using namespace std::chrono_literals;

namespace game {

Manager::Manager() : Selector() {}

Manager::~Manager() {}

void Manager::registerHandle(std::unique_ptr<io::hdl::Client> &hdl)
{
	auto found(false);

	for (auto it = _waitingGames.begin();
		it != _waitingGames.end() && !found; std::advance(it, 1)) {
		it->gameptr->processMsg(*hdl, "");

		found = true;
		hdl->setMsgProcessor(_waitingGames.back().game);
		if (it->gameptr->full()) {
			it->gameptr->start();
			_processors.emplace_back(it->gameptr);
			it = _waitingGames.erase(it);
		}
		if (it->gameptr->ready())
			it->tp = std::chrono::system_clock::now();
	}

	if (!found) {
		auto *nGame = new MilleBornes;
		if (!nGame) throw std::runtime_error("Out of memory");
		_waitingGames.emplace_back();
		_waitingGames.back().game.reset(nGame);
		_waitingGames.back().gameptr = nGame;
		_waitingGames.back().game->processMsg(*hdl, "");
		hdl->setMsgProcessor(_waitingGames.back().game);
	}

	io::hdl::IHandle *interfacedHdl = hdl.release();
	_handles.emplace_back(interfacedHdl);
}

void Manager::registerHandle(std::unique_ptr<io::hdl::IHandle> &hdl)
{
	std::cout << "regspe\n";
	if (hdl->getType() == io::hdl::HType::CLIENT) {
		std::cout << "regspe2\n";
		auto *client = static_cast<io::hdl::Client *>(hdl.release());
		std::unique_ptr<io::hdl::Client> uniqueClient(client);
		this->registerHandle(uniqueClient);
	} else {
		std::cout << "regspe3\n";
		this->Selector::registerHandle(hdl);
	}
}

bool Manager::run()
{
	auto ret(this->Selector::run());
	auto now(std::chrono::system_clock::now());

	for (auto it(_waitingGames.begin()); it != _waitingGames.end();
		std::advance(it, 1)) {
		if (it->gameptr->ready() && now - it->tp > 2s) {
			it->gameptr->start();
			_processors.emplace_back(it->gameptr);
			it = _waitingGames.erase(it);
		}
	}

	return ret;
}

} // namespace game
