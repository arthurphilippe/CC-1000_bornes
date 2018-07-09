/*
** COBRA CODING CLUB PROJECT
** PSU_myirc_2017
** File description:
** list
*/

#include "list.h"
#include <stdlib.h>

list_t *list_create(void (*data_destructor)(void *))
{
	list_t *new_list;

	new_list = malloc(sizeof(list_t));
	if (!new_list)
		return (NULL);
	new_list->l_start = NULL;
	new_list->l_end = NULL;
	new_list->l_size = 0;
	new_list->l_destructor = data_destructor;
	return (new_list);
}

static void list_node_destroy_rec(list_node_t *node, void (*dtor)(void *))
{
	if (node->n_next)
		list_node_destroy_rec(node->n_next, dtor);
	if (dtor)
		dtor(node->n_data);
	free(node);
}

void list_destroy(list_t *list)
{
	if (!list)
		return;
	if (list->l_start)
		list_node_destroy_rec(list->l_start, list->l_destructor);
	free(list);
}

static void list_erase_body(list_iter_t *iter, list_node_t *to_erase)
{
	list_node_t *prev = to_erase->n_prev;
	list_node_t *next = to_erase->n_next;

	if (prev)
		prev->n_next = next;
	else
		iter->li_list->l_start = next;
	if (next)
		next->n_prev = prev;
	else
		iter->li_list->l_end = prev;
	if (iter->li_list->l_destructor)
		iter->li_list->l_destructor(to_erase->n_data);
	free(to_erase);
	iter->li_list->l_size -= 1;
	iter->li_node = next;
}

void list_erase(list_iter_t *iter)
{
	list_node_t *to_erase = iter->li_node;

	if (iter->li_list->l_size == 1) {
		list_pop_front(iter->li_list);
		iter->li_node = NULL;
	} else if (to_erase)
		list_erase_body(iter, to_erase);
}
