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
	HazFlatTire, //		Disabled for 13-07-2018's session
	HazSpeedLimit, //	Disabled for 13-07-2018's session
	HazRedLight, //		Disabled for 13-07-2018's session

	DefRepair,
	DefGas,
	DefSpareWheel, //	Disabled for 13-07-2018's session
	DefEndOfLimit, //	Disabled for 13-07-2018's session
	DefGreenLight, //	Disabled for 13-07-2018's session

	SpeAcePilot,
	SpeTankLorry,
	SpePunctureProof, //	Disabled for 13-07-2018's session
	SpePrioritised, //	Disabled for 13-07-2018's session

	Dst25kms,
	Dst50kms,
	Dst75kms,
	Dst100kms,
	Dst200kms,

	COUNT,
	NONE,
} card_t;

#endif /* !CARD_H_ */
