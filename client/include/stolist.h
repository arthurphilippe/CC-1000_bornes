/*
** COBRA CODING CLUB PROJECT
** PSU_myirc_2017
** File description:
** stolist
*/

#ifndef STOLIST_H_
	#define STOLIST_H_

	#include "list.h"

list_t *stolist(const char *str, const char *spacers);
list_t *stolist_existing(list_t *list, const char *str, const char *spacers);

#endif /* !STOLIST_H_ */
