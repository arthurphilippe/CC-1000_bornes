/*
** COBRA CODING CLUB PROJECT
** client
** File description:
** strat
*/

#ifndef STRAT_H_
#define STRAT_H_

/**
 *  Forward delcarations
 */
typedef struct s_game game_t;

/**
 * Protos
 */
int strat_select_and_run(game_t *ga);
int strat_find_best_dist(game_t *ga);

#endif /* !STRAT_H_ */
