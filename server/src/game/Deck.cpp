/*
** COBRA CODING CLUB PROJECT
** server
** File description:
** Deck
*/

#include "Deck.hpp"

namespace game {

const std::unordered_map<Card, unsigned int> Deck::__cardDistribution{
	{Card::HazCarCrash, 6},
	{Card::HazGasOutage, 6},
	// {Card::HazFlatTire, 3},
	// {Card::HazSpeedLimit, 4},
	// {Card::HazRedLight, 5},
	{Card::DefRepair, 9},
	{Card::DefGas, 9},
	// {Card::DefSpareWheel, 6},
	// {Card::DefEndOfLimit, 6},
	// {Card::DefGreenLight, 14},
	{Card::SpeAcePilot, 1},
	{Card::SpeTankLorry, 1},
	// {Card::SpePunctureProof, 1},
	// {Card::SpePrioritised, 1},
	{Card::Dst25kms, 10},
	{Card::Dst50kms, 10},
	{Card::Dst75kms, 10},
	{Card::Dst100kms, 12},
	{Card::Dst200kms, 4},
};

Deck::Deck()
	: _remainToDistribute(__cardDistribution),
	  _generator(
		  std::chrono::system_clock::now().time_since_epoch().count())
{
	while (!_remainToDistribute.empty()) {
		auto idx = _generator();
		idx %= static_cast<unsigned int>(Card::COUNT);
		auto card = static_cast<Card>(idx);
		if (_remainToDistribute.find(card) !=
			_remainToDistribute.end()) {
			_cards.push_back(card);
			_remainToDistribute[card] -= 1;
			if (!_remainToDistribute[card])
				_remainToDistribute.erase(card);
		}
	}
}

Deck::~Deck() {}

} // namespace game
