/*
** COBRA CODING CLUB PROJECT
** server
** File description:
** MilleBornes
*/

#include "MilleBornes.hpp"
#include <iostream>
#include "tools/Parsing.hpp"

namespace game {

MilleBornes::MilleBornes()
	: _deck(),
	  _players(),
	  _live(true),
	  _started(false),
	  _currentPlayer(_players.begin())
{}

MilleBornes::~MilleBornes() {}

void MilleBornes::processMsg(io::hdl::Client &handle, const std::string &msg)
{
	try {
		auto &pl = _controlAccess(handle);
		if (!msg.empty() && _started &&
			_currentPlayer->client.id != handle.id) {
			pl.client.stream() << "not_your_turn" << std::endl;
		} else if (!msg.empty() && _started) {
			auto splitMsg =
				tools::Parsing::createVectorString(msg, ' ');
		}
		handle.dumpStream();
	} catch (const std::exception &) {
		throw;
	} catch (...) {
		throw std::runtime_error("no room left");
	}
}

void MilleBornes::onCycle() {}

void MilleBornes::start()
{
	_currentPlayer = _players.begin();
	for (auto &pl : _players) {
		dump(pl.client.stream(), _players);
		pl.client.dumpStream();
		for (auto &card : pl.hand) {
			card = _deck.drawCard();
		}
	}
	_started = true;
}

void MilleBornes::runCmd(Player &pl, std::vector<std::string> &splitCmd)
{
	if (splitCmd.size() <= 1) return;

	unsigned int nb;
	try {
		nb = std::stoi(splitCmd[1]);
	} catch (...) {
		return;
	}

	auto ret(false);
	if (splitCmd.front() == "use" && splitCmd.size() == 2) {
		ret = useCard(pl, pl.hand[nb]);
	} else if (splitCmd.front() == "use" && splitCmd.size() == 3) {
		try {
			auto id(std::stoul(splitCmd[2]));
			ret = useCard(pl, pl.hand[nb], _getPlayer(id));
		} catch (...) {
			return;
		}
	} else if (splitCmd.front() == "discard") {
		_deck.throwAway(pl.hand[nb]);
		pl.hand[nb] = Card::NONE;
		ret = true;
	}
	if (ret) {
		pl.client.stream() << "ok" << std::endl;
		_nextPlayer();
	}
}

MilleBornes::Player &MilleBornes::_controlAccess(io::hdl::Client &handle)
{
	try {
		auto &pl = this->_getPlayer(handle.id);
		return pl;
	} catch (...) {
		if (_players.size() < MAX_PLAYER) {
			Player tmpPl{
				{}, handle, 0, Card::NONE, 0, 0, 0, 0, 0, 0};
			tmpPl.hand.fill(Card::NONE);
			_players.push_back(std::move(tmpPl));
			_currentPlayer = _players.begin();
			handle.stream() << "id " << handle.id << std::endl;
			handle.dumpStream();
		}
	}
	return this->_getPlayer(handle.id);
}

MilleBornes::Player &MilleBornes::_getPlayer(unsigned long id)
{
	for (auto &pl : _players)
		if (pl.client.id == id) return (pl);
	throw 0;
}

bool MilleBornes::useCard(MilleBornes::Player &pl, Card &card)
{
	auto ret(false);
	switch (card) {
	case Card::DefRepair... Card::DefGreenLight:
		ret = useDefense(pl, card);
		break;
	case Card::SpeAcePilot... Card::SpePrioritised:
		ret = useSpecial(pl, card);
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

bool MilleBornes::useCard(Player &pl, Card &card, Player &foe)
{
	auto ret(false);
	if (card <= Card::HazRedLight) {
		ret = useHazard(pl, card, foe);
	}
	if (ret) card = Card::NONE;
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
			totDist = 1001;
			break;
		}
		if (totDist <= 1000) {
			pl.distance = totDist;
			ret = true;
			if (pl.distance == 1000) this->_onVictory();
		}
	}
	return ret;
}

bool MilleBornes::useDefense(MilleBornes::Player &pl, Card &card)
{
	auto cardCode(static_cast<unsigned int>(card));
	auto hazard(static_cast<unsigned int>(pl.hazard));
	auto ret(false);
	if (pl.hazard != Card::NONE && (cardCode - 5U) == hazard) {
		pl.hazard = Card::NONE;
		ret = true;
	} else if (pl.speedlimited && card == Card::DefEndOfLimit) {
		pl.speedlimited = false;
		ret = true;
	}
	return ret;
}

bool MilleBornes::useHazard(Player &pl, Card &card, Player &other)
{
	(void) pl;
	auto ret(true);
	if ((other.hazard != Card::NONE && card != Card::HazSpeedLimit) ||
		(card == Card::HazCarCrash && other.acePilot) ||
		(card == Card::HazGasOutage && other.tankLorry) ||
		(card == Card::HazFlatTire && other.punctureProof) ||
		(card == Card::HazRedLight && other.pioritised) ||
		(card == Card::HazSpeedLimit && other.pioritised))
		ret = false;
	else if (card != Card::HazSpeedLimit)
		other.hazard = card;
	else
		other.speedlimited = true;
	return ret;
}

bool MilleBornes::useSpecial(Player &pl, Card &card)
{
	auto ret(true);
	switch (card) {
	case Card::SpeAcePilot:
		pl.acePilot = true;
		break;
	case Card::SpeTankLorry:
		pl.tankLorry = true;
		if (pl.hazard == Card::HazGasOutage) pl.hazard = Card::NONE;
		break;
	case Card::SpePunctureProof:
		pl.punctureProof = true;
		if (pl.hazard == Card::HazFlatTire) pl.hazard = Card::NONE;
		break;
	case Card::SpePrioritised:
		pl.pioritised = true;
		if (pl.hazard == Card::HazRedLight) pl.hazard = Card::NONE;
		if (pl.speedlimited) pl.speedlimited = false;
		break;
	default:
		break;
		ret = false;
	}
	return ret;
}

// TODO: Send msg to everyone
void MilleBornes::_onVictory()
{
	for (auto &it : _players) {
		it.client.stream() << "winner " << _currentPlayer->client.id
				   << std::endl;
		it.client.setLive(false);
	}
	_live = false;
}

} // namespace game
