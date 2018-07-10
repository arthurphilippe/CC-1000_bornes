/*
** COBRA CODING CLUB PROJECT
** PSU_myirc_2017
** File description:
** stolist
*/

#ifndef STOLIST_H_
#define STOLIST_H_

#include "list.h"

/**
 * stolist takes a string to process and a string of spacers.
 * The string to process will be cut into a list of words.
 * The list of words will not cotain any of the spacers
 * even if they repeat themsselves.
 * The caller because the owner of the list and is reponsible for its
 * deletion.
 */
list_t *stolist(const char *str, const char *spacers);

/**
 * stolist_existing has the same functionality as stolist but instead of
 * creating a new list, it will fill an existing one. (hence it's name.)
 */
list_t *stolist_existing(list_t *list, const char *str, const char *spacers);

#endif /* !STOLIST_H_ */
