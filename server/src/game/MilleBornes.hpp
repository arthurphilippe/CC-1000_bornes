/*
** COBRA CODING CLUB PROJECT
** server
** File description:
** MilleBornes
*/

#ifndef MILLEBORNES_HPP_
#define MILLEBORNES_HPP_

#include <iostream>
#include <list>
#include <vector>
#include "Card.hpp"
#include "Deck.hpp"
#include "io/hdl/Client.hpp"
#include "io/hdl/IMsgProcessor.hpp"

namespace game {

constexpr auto MAX_PLAYER(6);
constexpr auto MIN_PLAYER(6);

class MilleBornes : public io::hdl::IMsgProcessor {
public:
	struct Player {
		std::array<Card, 6> hand;
		io::hdl::Client &client;
		unsigned int distance;
		Card hazard;
		bool speedlimited;
		bool acePilot;
		bool tankLorry;
		bool punctureProof;
		bool pioritised;
	};
	MilleBornes();
	~MilleBornes();
	void processMsg(
		io::hdl::Client &handle, const std::string &msg) override;
	void onCycle();
	void start();
	bool live() const noexcept override { return _live; }
	bool ready() const noexcept { return (_players.size() >= 2); }
	bool full() const noexcept { return (_players.size() >= 6); }

	bool useCard(Player &pl, Card &card);
	bool useCard(Player &pl, Card &card, Player &foe);
	bool useDefense(Player &pl, Card &card);
	bool useDist(Player &pl, Card &card);
	bool useHazard(Player &pl, Card &card, Player &foe);
	bool useSpecial(Player &pl, Card &card);

	void runCmd(Player &pl, std::vector<std::string> &splitCmd);

private:
	Player &_getPlayer(unsigned long id);
	Player &_controlAccess(io::hdl::Client &handle);

	void _onVictory();
	void _nextPlayer()
	{
		if (_currentPlayer != _players.end())
			std::advance(_currentPlayer, 1);
		if (_currentPlayer == _players.end())
			_currentPlayer = _players.begin();
		dump(_currentPlayer->client.stream(), _currentPlayer->hand);
		for (auto &pl : _players)
			dump(_currentPlayer->client.stream(), pl);
		_currentPlayer->client.stream() << "your_turn" << std::endl;
		_currentPlayer->client.dumpStream();
	}

	void _quit(unsigned long id);
	void _end();

	static inline Card &_playerSelectCard(Player &pl, Card selection)
	{
		for (auto &card : pl.hand) {
			if (card == selection) return card;
		}
		throw 0;
	}

	static inline void dump(std::ostream &os, const Player &pl)
	{
		os << "playerstate " << pl.client.id << " " << pl.distance
		   << " " << pl.hazard << " " << pl.speedlimited << " "
		   << pl.acePilot << " " << pl.tankLorry << " "
		   << pl.punctureProof << " " << pl.pioritised << std::endl;
	}
	static inline void dump(
		std::ostream &os, const std::list<Player> &players)
	{
		os << "lsplayers";
		for (const auto &pl : players) os << " " << pl.client.id;
		os << std::endl;
	}
	static inline void dump(std::ostream &os, std::array<Card, 6> &cards)
	{
		os << "lscards";
		for (auto &card : cards) {
			os << " " << card;
		}
		os << std::endl;
	}

	Deck _deck;
	std::list<Player> _players;
	bool _live;
	bool _started;
	std::list<Player>::iterator _currentPlayer;
};

} // namespace game

#endif /* !MILLEBORNES_HPP_ */
