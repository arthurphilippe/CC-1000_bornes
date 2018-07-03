/*
** COBRA CODING CLUB PROJECT
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
		io::hdl::Client &client;
		unsigned int distance;
		Card hazard;
		bool speedlimited;
		bool light;
		bool acePilot;
		bool tankLorry;
		bool punctureProof;
		bool pioritised;
	};
	MilleBornes();
	~MilleBornes();
	void processMsg(
		io::hdl::Client &handle, const std::string &msg) override;
	bool live() const noexcept override { return _live; }
	bool ready() const noexcept { return (_players.size() >= 2); }
	bool full() const noexcept { return (_players.size() >= 6); }

	bool useCard(Player &pl, Card &card);
	bool useCard(Player &pl, Card &card, Player &foe);
	bool useDefense(Player &pl, Card &card);
	bool useDist(Player &pl, Card &card);
	bool useHazard(Player &pl, Card &card, Player &foe);
	bool useSpecial(Player &pl, Card &card);

private:
	Player &_getPlayer(unsigned long id);
	Player &_controlAccess(io::hdl::Client &handle);

	void _onVictory();

	Card &_playerSelectCard(Player &pl, Card selection)
	{
		for (auto &card : pl.hand) {
			if (card == selection) return card;
		}
		throw 0;
	}

	Deck _deck;
	std::list<Player> _players;
	bool _live;
};

} // namespace game

#endif /* !MILLEBORNES_HPP_ */
