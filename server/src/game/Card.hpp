/*
** EPITECH PROJECT, 2018
** server
** File description:
** Card
*/

#ifndef CARD_HPP_
#define CARD_HPP_

namespace game {
enum class Card {
	AttCarCrash,
	AttGasOutage,
	AttFlatTire,
	AttSpeedLimit,
	AttRedLight,

	DefRepair,
	DefGas,
	DefSpareWheel,
	DefEndOfLimit,
	DefGreenLight,

	SpeAcePilot,
	SpeTankLorry,
	SpePunctureProof,
	SpePrioritised,

	Dst25kms,
	Dst50kms,
	Dst75kms,
	Dst100kms,
	Dst200kms,
};
}
#endif /* !CARD_HPP_ */
