/*
** COBRA CODING CLUB PROJECT
** server
** File description:
** MilleBornes
*/

#include "MilleBornes.hpp"
#include <iostream>
#include "io/hdl/Client.hpp"

namespace game {

MilleBornes::MilleBornes() : _deck(), _players(), _live(true) {}

MilleBornes::~MilleBornes() {}

void MilleBornes::processMsg(io::hdl::Client &handle, const std::string &msg)
{
	(void) msg;
	Player *pl = nullptr;
	if (_controlAccess(handle, pl)) {
	}
}

bool MilleBornes::_controlAccess(
	io::hdl::Client &handle, MilleBornes::Player *&pl)
{
	auto ret = false;
	for (auto &it : _players) {
		if (it.client.id == handle.id) {
			ret = true;
			pl = &it;
			break;
		}
	}
	if (!ret && _players.size() < MAX_PLAYER) {
		Player tmpPl{{}, handle, 0, Card::NONE, false, false};
		tmpPl.hand.fill(Card::NONE);
		_players.push_back(std::move(tmpPl));
		_controlAccess(handle, pl);
		ret = true;
	}
	return (ret);
}

bool MilleBornes::useCard(MilleBornes::Player &pl, Card &card)
{
	auto ret(false);
	switch (card) {
	case Card::DefRepair... Card::DefGreenLight:
		ret = useDefense(pl, card);
		break;
	case Card::SpeAcePilot... Card::SpePrioritised:
		break;
	case Card::Dst25kms... Card::Dst200kms:
		ret = useDist(pl, card);
		break;
	default:
		break;
	}
	if (ret) card = Card::NONE;
	return ret;
}

bool MilleBornes::useCard(MilleBornes::Player &pl, Card &card, Player &foe)
{
	auto ret(false);
	if (card >= Card::HazCarCrash && card <= Card::HazRedLight) {
		ret = useHazard(pl, card, foe);
	}
	return (ret);
}

bool MilleBornes::useDist(MilleBornes::Player &pl, Card &card)
{
	auto ret(false);
	auto totDist(pl.distance);
	if (pl.hazard == Card::NONE && pl.light &&
		(!pl.speedlimited || card <= Card::Dst50kms)) {
		switch (card) {
		case Card::Dst25kms:
			totDist += 25;
			break;
		case Card::Dst50kms:
			totDist += 50;
			break;
		case Card::Dst75kms:
			totDist += 75;
			break;
		case Card::Dst100kms:
			totDist += 100;
			break;
		case Card::Dst200kms:
			totDist += 200;
			break;
		default:
			break;
		}
		if (totDist <= 1000) {
			pl.distance = totDist;
			ret = true;
		}
	}
	return ret;
}

bool MilleBornes::useDefense(MilleBornes::Player &pl, Card &card)
{
	auto cardCode(static_cast<unsigned int>(card));
	auto hazard(static_cast<unsigned int>(pl.hazard));
	auto ret(false);
	std::cout << "card code: " << cardCode << " | hazard: " << hazard
		  << std::endl;
	if (pl.hazard != Card::NONE && (cardCode - 5U) == hazard) {
		std::cout << "reset\n";
		pl.hazard = Card::NONE;
		ret = true;
	}
	return (ret);
}

bool MilleBornes::useHazard(Player &pl, Card &card, Player &other)
{
	(void) pl;
	auto ret(true);
	if (other.hazard != Card::NONE)
		ret = false;
	else
		other.hazard = card;
	return ret;
}

MilleBornes::Player &MilleBornes::_targetPlayer(unsigned long id)
{
	for (auto &pl : _players)
		if (pl.client.id == id) return (pl);
	throw;
}

} // namespace game
