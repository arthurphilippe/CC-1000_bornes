/*
** EPITECH PROJECT, 2018
** client
** File description:
** player_state
*/

#ifndef PLAYER_STATE_H_
#define PLAYER_STATE_H_

#include "card.h"

typedef struct s_player_state {
	unsigned long ps_id;
	unsigned int ps_dist;
	card_t ps_incident;
	bool ps_ace;
	bool ps_tank;
	bool ps_puncture_proof;
	bool ps_prioritised;
} player_state_t;

#endif /* !PLAYER_STATE_H_ */
