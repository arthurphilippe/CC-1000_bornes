/*
** EPITECH PROJECT, 2018
** server
** File description:
** MilleBornes
*/

#include "MilleBornes.hpp"
#include "io/hdl/Client.hpp"

namespace game {

MilleBornes::MilleBornes() : _deck(), _players(), _live(true) {}

MilleBornes::~MilleBornes() {}

void MilleBornes::processMsg(io::hdl::Client &handle, const std::string &msg)
{
	(void) msg;
	if (_controlAccess(handle)) {
	}
}

bool MilleBornes::_controlAccess(io::hdl::Client &handle)
{
	auto ret = false;
	for (const auto &it : _players) {
		if (it.client.id == handle.id) {
			ret = true;
			break;
		}
	}
	if (!ret && _players.size() < MAX_PLAYER) {
		Player tmpPl{{}, 0, handle, Card::NONE, false, false};
		tmpPl.hand.fill(Card::NONE);
		_players.push_back(std::move(tmpPl));
		ret = true;
	}
	return (ret);
}

} // namespace game
