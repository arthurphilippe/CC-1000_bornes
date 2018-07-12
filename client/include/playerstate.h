/*
** COBRA CODING CLUB PROJECT
** client
** File description:
** playerstate
*/

#ifndef playerstate_H_
#define playerstate_H_

#include <stdbool.h>
#include "card.h"

typedef struct s_playerstate {
	unsigned long ps_id;
	unsigned int ps_dist;
	card_t ps_incident;
	bool ps_limited;
	bool ps_ace;
	bool ps_tank;
	bool ps_puncture_proof;
	bool ps_prioritised;
} playerstate_t;

#endif /* !playerstate_H_ */
