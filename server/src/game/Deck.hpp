/*
** COBRA CODING CLUB PROJECT
** server
** File description:
** Deck
*/

#ifndef DECK_HPP_
#define DECK_HPP_

#include <chrono>
#include <list>
#include <random>
#include <unordered_map>
#include "game/Card.hpp"

namespace game {

class Deck {
public:
	Deck();
	~Deck();

	const std::list<Card> &getCards() const noexcept { return _cards; }
	Card drawCard() noexcept
	{
		auto ret = _cards.front();
		_cards.pop_front();
		return (ret);
	}
	void throwAway(Card card) { _cards.push_back(card); }

private:
	std::unordered_map<Card, unsigned int> _remainToDistribute;

	std::list<Card> _cards;

	std::mt19937 _generator;

	static const std::unordered_map<Card, unsigned int>
		__cardDistribution;
};

} // namespace game

#endif /* !DECK_HPP_ */
