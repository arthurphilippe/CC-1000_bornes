/*
** COBRA CODING CLUB PROJECT
** PSU_myirc_2017
** File description:
** list
*/

#ifndef LIST_H_
	#define LIST_H_

	#include <stddef.h>
	#include <stdbool.h>

	#define LIST_ERR -1
	#define LIST_OK 0

typedef struct	s_list_node {
	void	*n_data;
	void	*n_next;
	void	*n_prev;
}		list_node_t;

typedef struct		s_list {
	list_node_t	*l_start;
	list_node_t	*l_end;
	size_t		l_size;
	void		(*l_destructor)(void *);
}			list_t;

typedef enum	e_list_iter_mode {
		FWD,
		BCKW,
}		list_iter_mode_t;

typedef struct			s_list_iterator {
	list_t			*li_list;
	list_node_t		*li_node;
	list_iter_mode_t	li_mode;
}				list_iter_t;

/*
** Prototypes
*/
list_t *list_create(void (*data_destructor)(void *));
void list_destroy(list_t *list);
int list_push_back(list_t *list, void *payload);
int list_push_front(list_t *list, void *payload);
void *list_get_front(list_t *list);
void *list_get_back(list_t *list);
size_t list_get_size(list_t *list);
void list_pop_front(list_t *list);
void list_pop_back(list_t *list);
void list_erase(list_iter_t *iter);

list_iter_t *list_iter_create(list_t *list, list_iter_mode_t mode);
void *list_iter_next(list_iter_t *iter);
void *list_iter_access(list_iter_t *iter);
list_iter_t *list_find_addr(list_t *list, void *addr);
bool list_find_and_delete_addr(list_t *list, void *addr);
void list_iter_init(list_iter_t *iter, list_t *list, list_iter_mode_t mode);

#endif /* !LIST_H_ */
