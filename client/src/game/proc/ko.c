/*
** COBRA CODING CLUB PROJECT
** client
** File description:
** ko
*/

#include <stdio.h>
#include "game.h"
#include "game/proc.h"

void game_proc_ko(game_t *ga, list_t *msg)
{
	(void) msg;
	ga->ga_carry = false;
	printf(" !-> %s\n\n", "Your last action failed");
}
