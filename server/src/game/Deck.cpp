/*
** EPITECH PROJECT, 2018
** server
** File description:
** Deck
*/

#include "Deck.hpp"

namespace game {

const std::unordered_map<Card, unsigned int> Deck::__cardDistribution{
	{Card::AttCarCrash, 3},
	{Card::AttGasOutage, 3},
	{Card::AttFlatTire, 3},
	{Card::AttSpeedLimit, 4},
	{Card::AttRedLight, 5},
	{Card::DefRepair, 6},
	{Card::DefGas, 6},
	{Card::DefSpareWheel, 6},
	{Card::DefEndOfLimit, 6},
	{Card::DefGreenLight, 14},
	{Card::SpeAcePilot, 1},
	{Card::SpeTankLorry, 1},
	{Card::SpePunctureProof, 1},
	{Card::SpePrioritised, 1},
	{Card::Dst25kms, 10},
	{Card::Dst50kms, 10},
	{Card::Dst75kms, 10},
	{Card::Dst100kms, 12},
	{Card::Dst200kms, 4},
};

Deck::Deck() : _remainToDistribute(__cardDistribution) {}

Deck::~Deck() {}

} // namespace game
