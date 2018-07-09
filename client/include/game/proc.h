/*
** EPITECH PROJECT, 2018
** client
** File description:
** proc
*/

#ifndef PROC_H_
#define PROC_H_

typedef struct s_game game_t;
typedef struct s_list list_t;

typedef struct s_proc_key {
	const char *pk_str;
	void (*pk_func)(game_t *ga, list_t *msg);
} proc_key_t;

#endif /* !PROC_H_ */
