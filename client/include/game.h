/*
** EPITECH PROJECT, 2018
** client
** File description:
** game
*/

#ifndef GAME_H_
#define GAME_H_

#include "player_state.h"

typedef struct s_game {
	unsigned long ga_id;
	player_state_t ga_players[6];
	card_t ga_hand[6];
} game_t;

#endif /* !GAME_H_ */
