/*
** COBRA CODING CLUB PROJECT
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
	player_state_t ga_self;
	card_t ga_hand[6];
	unsigned long ga_id;
	unsigned long ga_id_winner;
	unsigned int ga_player_nb;
	int ga_socketfd;
	bool ga_live;
	bool ga_carry;
} game_t;

// Prototypes
game_t *game_create(void);
void game_delete(void *ptr);
int game_connect(game_t *ga, const char *arg_str);
bool game_read(game_t *ga);
bool game_use_card(game_t *ga, unsigned int idx);
bool game_use_attack(game_t *ga, unsigned int idx, unsigned int idx_target);
bool game_use_attack_by_id(game_t *ga, unsigned int idx, unsigned long id);
bool game_discard_card(game_t *ga, unsigned int idx);

#endif /* !GAME_H_ */
