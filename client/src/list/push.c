/*
** COBRA CODING CLUB PROJECT
** PSU_myirc_2017
** File description:
** list_push
*/

#include <stdlib.h>
#include "list.h"

static void list_node_add_first(list_t *list, list_node_t *fst_node)
{
	fst_node->n_next = NULL;
	fst_node->n_prev = NULL;
	list->l_start = fst_node;
	list->l_end = fst_node;
}

int list_push_back(list_t *list, void *payload)
{
	list_node_t *new_node = malloc(sizeof(list_node_t));

	if (!new_node)
		return (LIST_ERR);
	new_node->n_data = payload;
	if (list->l_end == NULL) {
		list_node_add_first(list, new_node);
	} else {
		list->l_end->n_next = new_node;
		new_node->n_prev = list->l_end;
		new_node->n_next = NULL;
		list->l_end = new_node;
	}
	list->l_size += 1;
	return (LIST_OK);
}

int list_push_front(list_t *list, void *payload)
{
	list_node_t *new_node = malloc(sizeof(list_node_t));

	if (!new_node)
		return (LIST_ERR);
	new_node->n_data = payload;
	if (list->l_start == NULL) {
		list_node_add_first(list, new_node);
	} else {
		list->l_start->n_prev = new_node;
		new_node->n_next = list->l_start;
		new_node->n_prev = NULL;
		list->l_start = new_node;
	}
	list->l_size += 1;
	return (LIST_OK);
}
