/*
** COBRA CODING CLUB PROJECT
** client
** File description:
** card
*/

#ifndef CARD_H_
#define CARD_H_

typedef enum e_card {
	HazCarCrash = 0,
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
} card_t;

#endif /* !CARD_H_ */
