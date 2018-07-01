/*
** EPITECH PROJECT, 2018
** server
** File description:
** Deck
*/

#ifndef DECK_HPP_
#define DECK_HPP_

#include <unordered_map>
#include "game/Card.hpp"

namespace game {

class Deck {
public:
	Deck();
	~Deck();

private:
	std::unordered_map<Card, unsigned int> _remainToDistribute;

	static const std::unordered_map<Card, unsigned int>
		__cardDistribution;
};

} // namespace game

#endif /* !DECK_HPP_ */
