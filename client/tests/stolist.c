/*
** COBRA CODING CLUB PROJECT
** PSU_myirc_2017
** File description:
** stolist
*/

#include "stolist.h"
#include <criterion/assert.h>
#include <criterion/criterion.h>

Test(stolist, one_word)
{
	list_t *words = stolist("toto", " ");

	cr_assert(words);
	cr_assert(words->l_start);
	cr_assert_str_eq(words->l_start->n_data, "toto");
	list_destroy(words);
}

Test(stolist, one_word_no_spacer)
{
	list_t *words = stolist("toto", "");

	cr_assert(words);
	cr_assert(words->l_start);
	cr_assert_str_eq(words->l_start->n_data, "toto");
	list_destroy(words);
}

Test(stolist, multiple_words)
{
	list_t *words = stolist("toto va a   la plage avec ses khey et\
 sa   serviette",
		" ");

	cr_assert(words);
	list_iter_t *iter = list_iter_create(words, FWD);
	cr_assert(iter);
	cr_assert_str_eq(list_iter_access(iter), "toto");
	list_iter_next(iter);
	cr_assert_str_eq(list_iter_access(iter), "va");
	list_iter_next(iter);
	cr_assert_str_eq(list_iter_access(iter), "a");
	list_iter_next(iter);
	cr_assert_str_eq(list_iter_access(iter), "la");
	list_iter_next(iter);
	cr_assert_str_eq(list_iter_access(iter), "plage");
	list_iter_next(iter);
	cr_assert_str_eq(list_iter_access(iter), "avec");
	list_iter_next(iter);
	cr_assert_str_eq(list_iter_access(iter), "ses");
	list_iter_next(iter);
	cr_assert_str_eq(list_iter_access(iter), "khey");
	list_iter_next(iter);
	cr_assert_str_eq(list_iter_access(iter), "et");
	list_iter_next(iter);
	cr_assert_str_eq(list_iter_access(iter), "sa");
	list_iter_next(iter);
	cr_assert_str_eq(list_iter_access(iter), "serviette");
	list_iter_next(iter);
	list_destroy(words);
	free(iter);
}

Test(stolist, multiple_words_and_spacers)
{
	list_t *words = stolist("toto va a   la plage avec ses khey et\
 sa   serviette ; mais sans son code civil. nous,sommes,separes,\
 par,des ,virgules,",
		", ;.");

	cr_assert(words);
	list_iter_t *iter = list_iter_create(words, FWD);
	cr_assert(iter);
	cr_assert_str_eq(list_iter_access(iter), "toto");
	list_iter_next(iter);
	cr_assert_str_eq(list_iter_access(iter), "va");
	list_iter_next(iter);
	cr_assert_str_eq(list_iter_access(iter), "a");
	list_iter_next(iter);
	cr_assert_str_eq(list_iter_access(iter), "la");
	list_iter_next(iter);
	cr_assert_str_eq(list_iter_access(iter), "plage");
	list_iter_next(iter);
	cr_assert_str_eq(list_iter_access(iter), "avec");
	list_iter_next(iter);
	cr_assert_str_eq(list_iter_access(iter), "ses");
	list_iter_next(iter);
	cr_assert_str_eq(list_iter_access(iter), "khey");
	list_iter_next(iter);
	cr_assert_str_eq(list_iter_access(iter), "et");
	list_iter_next(iter);
	cr_assert_str_eq(list_iter_access(iter), "sa");
	list_iter_next(iter);
	cr_assert_str_eq(list_iter_access(iter), "serviette");
	list_iter_next(iter);
	cr_assert_str_eq(list_iter_access(iter), "mais");
	list_iter_next(iter);
	cr_assert_str_eq(list_iter_access(iter), "sans");
	list_iter_next(iter);
	cr_assert_str_eq(list_iter_access(iter), "son");
	list_iter_next(iter);
	cr_assert_str_eq(list_iter_access(iter), "code");
	list_iter_next(iter);
	cr_assert_str_eq(list_iter_access(iter), "civil");
	list_iter_next(iter);
	cr_assert_str_eq(list_iter_access(iter), "nous");
	list_iter_next(iter);
	cr_assert_str_eq(list_iter_access(iter), "sommes");
	list_iter_next(iter);
	cr_assert_str_eq(list_iter_access(iter), "separes");
	list_iter_next(iter);
	cr_assert_str_eq(list_iter_access(iter), "par");
	list_iter_next(iter);
	cr_assert_str_eq(list_iter_access(iter), "des");
	list_iter_next(iter);
	cr_assert_str_eq(list_iter_access(iter), "virgules");
	list_iter_next(iter);
	list_destroy(words);
	free(iter);
}

Test(stolist_suffixed, one_word)
{
	list_t *words = stolist_suffixed("toto", " ");

	cr_assert(words);
	cr_assert(words->l_start);
	cr_assert_str_eq(words->l_start->n_data, "toto");
	list_destroy(words);
}

Test(stolist_suffixed, one_word_no_spacer)
{
	list_t *words = stolist_suffixed("toto", "");

	cr_assert(words);
	cr_assert(words->l_start);
	cr_assert_str_eq(words->l_start->n_data, "toto");
	list_destroy(words);
}

Test(stolist_suffixed, multiple_words)
{
	list_t *words =
		stolist_suffixed("toto va a   la plage avec ses khey et\
 sa   serviette :je ne suis pas découpé parce que je suis précédé par deux-points",
			" ");

	cr_assert(words);
	list_iter_t *iter = list_iter_create(words, FWD);
	cr_assert(iter);
	cr_assert_str_eq(list_iter_access(iter), "toto");
	list_iter_next(iter);
	cr_assert_str_eq(list_iter_access(iter), "va");
	list_iter_next(iter);
	cr_assert_str_eq(list_iter_access(iter), "a");
	list_iter_next(iter);
	cr_assert_str_eq(list_iter_access(iter), "la");
	list_iter_next(iter);
	cr_assert_str_eq(list_iter_access(iter), "plage");
	list_iter_next(iter);
	cr_assert_str_eq(list_iter_access(iter), "avec");
	list_iter_next(iter);
	cr_assert_str_eq(list_iter_access(iter), "ses");
	list_iter_next(iter);
	cr_assert_str_eq(list_iter_access(iter), "khey");
	list_iter_next(iter);
	cr_assert_str_eq(list_iter_access(iter), "et");
	list_iter_next(iter);
	cr_assert_str_eq(list_iter_access(iter), "sa");
	list_iter_next(iter);
	cr_assert_str_eq(list_iter_access(iter), "serviette");
	list_iter_next(iter);
	cr_assert_str_eq(list_iter_access(iter),
		"je ne suis pas découpé parce que je suis précédé par "
		"deux-points");
	list_iter_next(iter);

	list_destroy(words);
	free(iter);
}

Test(stolist_suffixed, multiple_words_and_spacers)
{
	list_t *words =
		stolist_suffixed("toto va a   la plage avec ses khey et\
 sa   serviette ; mais sans son code civil. nous,sommes,separes,\
 par,des ,virgules,:je ne suis pas découpé parce que je suis précédé par deux-points",
			", ;.");

	cr_assert(words);
	list_iter_t *iter = list_iter_create(words, FWD);
	cr_assert(iter);
	cr_assert_str_eq(list_iter_access(iter), "toto");
	list_iter_next(iter);
	cr_assert_str_eq(list_iter_access(iter), "va");
	list_iter_next(iter);
	cr_assert_str_eq(list_iter_access(iter), "a");
	list_iter_next(iter);
	cr_assert_str_eq(list_iter_access(iter), "la");
	list_iter_next(iter);
	cr_assert_str_eq(list_iter_access(iter), "plage");
	list_iter_next(iter);
	cr_assert_str_eq(list_iter_access(iter), "avec");
	list_iter_next(iter);
	cr_assert_str_eq(list_iter_access(iter), "ses");
	list_iter_next(iter);
	cr_assert_str_eq(list_iter_access(iter), "khey");
	list_iter_next(iter);
	cr_assert_str_eq(list_iter_access(iter), "et");
	list_iter_next(iter);
	cr_assert_str_eq(list_iter_access(iter), "sa");
	list_iter_next(iter);
	cr_assert_str_eq(list_iter_access(iter), "serviette");
	list_iter_next(iter);
	cr_assert_str_eq(list_iter_access(iter), "mais");
	list_iter_next(iter);
	cr_assert_str_eq(list_iter_access(iter), "sans");
	list_iter_next(iter);
	cr_assert_str_eq(list_iter_access(iter), "son");
	list_iter_next(iter);
	cr_assert_str_eq(list_iter_access(iter), "code");
	list_iter_next(iter);
	cr_assert_str_eq(list_iter_access(iter), "civil");
	list_iter_next(iter);
	cr_assert_str_eq(list_iter_access(iter), "nous");
	list_iter_next(iter);
	cr_assert_str_eq(list_iter_access(iter), "sommes");
	list_iter_next(iter);
	cr_assert_str_eq(list_iter_access(iter), "separes");
	list_iter_next(iter);
	cr_assert_str_eq(list_iter_access(iter), "par");
	list_iter_next(iter);
	cr_assert_str_eq(list_iter_access(iter), "des");
	list_iter_next(iter);
	cr_assert_str_eq(list_iter_access(iter), "virgules");
	list_iter_next(iter);
	cr_assert_str_eq(list_iter_access(iter),
		"je ne suis pas découpé parce que je suis précédé par "
		"deux-points");
	list_iter_next(iter);
	list_destroy(words);
	free(iter);
}
