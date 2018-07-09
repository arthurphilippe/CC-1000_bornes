/*
** COBRA CODING CLUB PROJECT
** PSU_myirc_2017
** File description:
** list_pop
*/

#include <stdlib.h>
#include "list.h"

void list_pop_front(list_t *list)
{
	list_node_t *old_start = list->l_start;

	if (list->l_start) {
		list->l_start = list->l_start->n_next;
		if (list->l_start)
			list->l_start->n_prev = NULL;
		else
			list->l_end = NULL;
		if (list->l_destructor)
			list->l_destructor(old_start->n_data);
		free(old_start);
		list->l_size -= 1;
	}
}

void list_pop_back(list_t *list)
{
	list_node_t *old_end = list->l_end;

	if (old_end) {
		list->l_end = list->l_end->n_prev;
		if (list->l_end)
			list->l_end->n_next = NULL;
		else
			list->l_start = NULL;
		if (list->l_destructor)
			list->l_destructor(old_end->n_data);
		free(old_end);
		list->l_size -= 1;
	}
}
