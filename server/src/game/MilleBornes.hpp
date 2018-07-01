/*
** EPITECH PROJECT, 2018
** server
** File description:
** MilleBornes
*/

#ifndef MILLEBORNES_HPP_
#define MILLEBORNES_HPP_

#include <list>
#include <vector>
#include "Card.hpp"
#include "Deck.hpp"
#include "io/hdl/IMsgProcessor.hpp"

namespace game {

constexpr auto MAX_PLAYER(6);
constexpr auto MIN_PLAYER(6);

class MilleBornes : public io::hdl::IMsgProcessor {
public:
	struct Player {
		std::array<Card, 6> hand;
		unsigned int distance;
		io::hdl::Client &client;
		Card incident;
		bool speedlimited;
		bool light;
	};
	MilleBornes();
	~MilleBornes();
	void processMsg(io::hdl::Client &handle, const std::string &msg);
	bool live() const noexcept override { return _live; }
	bool ready() const noexcept { return (_players.size() >= 2); }
	bool full() const noexcept { return (_players.size() >= 6); }

private:
	bool _controlAccess(io::hdl::Client &handle);

	Deck _deck;
	std::list<Player> _players;
	bool _live;
};

} // namespace game

#endif /* !MILLEBORNES_HPP_ */
