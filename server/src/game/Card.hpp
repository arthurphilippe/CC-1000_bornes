/*
** COBRA CODING CLUB PROJECT
** server
** File description:
** Card
*/

#ifndef CARD_HPP_
#define CARD_HPP_

namespace game {

enum class Card : unsigned int {
	HazCarCrash,
	HazGasOutage,
	HazFlatTire,
	HazSpeedLimit,
	HazRedLight,

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

	COUNT,
	NONE,
};
}
#endif /* !CARD_HPP_ */
