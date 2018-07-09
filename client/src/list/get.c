/*
** COBRA CODING CLUB PROJECT
** PSU_myirc_2017
** File description:
** list_get
*/

#include "list.h"

void *list_get_front(list_t *list)
{
	if (list->l_start)
		return (list->l_start->n_data);
	return (NULL);
}

void *list_get_back(list_t *list)
{
	if (list->l_end)
		return (list->l_end->n_data);
	return (NULL);
}

size_t list_get_size(list_t *list)
{
	return list->l_size;
}
