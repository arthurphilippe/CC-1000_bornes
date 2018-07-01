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

namespace game {

class MilleBornes {
public:
	struct Player {
		std::list<Card> hand;
		unsigned int distance;
		unsigned int id;
		Card incident;
		bool speedlimited;
		bool light;
	};
	MilleBornes();
	~MilleBornes();

private:
	std::list<Player> _players;
};

} // namespace game

#endif /* !MILLEBORNES_HPP_ */
