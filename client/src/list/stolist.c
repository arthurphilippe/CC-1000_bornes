/*
** COBRA CODING CLUB PROJECT
** PSU_myirc_2017
** File description:
** str_to_list
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

static int push_back_substr(
	list_t *list, const char *str, const char *spacers)
{
	size_t cpy_size = strcspn(str, spacers);
	char *tmp;

	if (!cpy_size) return (cpy_size);
	tmp = calloc(sizeof(char), cpy_size + 1);
	if (!tmp) return (-1);
	strncpy(tmp, str, cpy_size);
	if (list_push_back(list, tmp) == LIST_OK) return (cpy_size);
	return (LIST_ERR);
}

list_t *stolist_existing(list_t *list, const char *str, const char *spacers)
{
	int i = 0;
	int ret;

	while (str[i]) {
		ret = push_back_substr(list, &str[i], spacers);
		if (ret == LIST_ERR) return (NULL);
		i += ret;
		i += strspn(&str[i], spacers);
	}
	return (list);
}

list_t *stolist(const char *str, const char *spacers)
{
	list_t *list = list_create(free);

	if (!list) return (NULL);
	if (!stolist_existing(list, str, spacers)) {
		list_destroy(list);
		return (NULL);
	}
	return (list);
}

static int wrap_push_back(
	list_t *list, const char *str, const char *spacers, int loop)
{
	if (loop && str[0] == ':')
		return (push_back_substr(list, &str[1], "") + 1);
	return (push_back_substr(list, str, spacers));
}

list_t *stolist_suffixed(const char *str, const char *spacers)
{
	list_t *list = list_create(free);
	int i = 0;
	int loop = 0;
	int ret;

	if (!list) return (NULL);
	while (str[i]) {
		ret = wrap_push_back(list, &str[i], spacers, loop);
		if (ret == LIST_ERR) {
			list_destroy(list);
			return (NULL);
		}
		i += ret;
		i += strspn(&str[i], spacers);
		loop++;
	}
	return (list);
}
