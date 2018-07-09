/*
** EPITECH PROJECT, 2018
** client
** File description:
** game
*/

#ifndef GAME_H_
#define GAME_H_

#include "player_state.h"

#ifndef NULL
#	define NULL (void *) 0
#endif /* NULL*/

// Game structure
typedef struct s_game {
	player_state_t ga_players[6];
	card_t ga_hand[6];
	unsigned long ga_id;
	unsigned long ga_id_winner;
	unsigned int ga_player_nb;
	bool ga_live;
} game_t;

// Prototypes
game_t *game_create(void);
void game_delete(void *ptr);

#endif /* !GAME_H_ */
