/*
** COBRA CODING CLUB PROJECT
** server
** File description:
** Deck
*/

#ifndef DECK_HPP_
#define DECK_HPP_

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

private:
	std::unordered_map<Card, unsigned int> _remainToDistribute;

	std::list<Card> _cards;

	std::random_device _rd;
	std::mt19937 _generator;

	static const std::unordered_map<Card, unsigned int>
		__cardDistribution;
};

} // namespace game

#endif /* !DECK_HPP_ */
