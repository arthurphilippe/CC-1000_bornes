/*
** COBRA CODING CLUB PROJECT
** client
** File description:
** proc
*/

#ifndef PROC_H_
#define PROC_H_

/*
 * Forward declarations
 */
typedef struct s_game game_t;
typedef struct s_list list_t;

/*
 * Proc map key structure
 */
typedef struct s_proc_key {
	const char *pk_str;
	void (*pk_func)(game_t *ga, list_t *msg);
} proc_key_t;

/*
 * Processors prototypes
 */
void game_proc(game_t *ga, const char *msg);
void game_proc_id(game_t *ga, list_t *msg);
void game_proc_lscards(game_t *ga, list_t *msg);
void game_proc_lsplayers(game_t *ga, list_t *msg);
void game_proc_playerstate(game_t *ga, list_t *msg);
void game_proc_winner(game_t *ga, list_t *msg);
void game_proc_ko(game_t *ga, list_t *msg);
void game_proc_ok(game_t *ga, list_t *msg);
void game_proc_info(game_t *ga, list_t *msg);

#endif /* !PROC_H_ */
