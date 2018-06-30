/*
** EPITECH PROJECT, 2018
** graphics
** File description:
** parserengine
*/

#include "tools/Parsing.hpp"
#include <criterion/criterion.h>
#include <iostream>

using Parsing = tools::Parsing;

Test(Parsing, basic)
{
	std::string str("Don't Blame Me Love Me Make Me Crazy");
	cr_assert_eq(Parsing::getStringFromArgNb(str, 0), "Don't");
	cr_assert_eq(Parsing::getStringFromArgNb(str, 1), "Blame");
	cr_assert_eq(Parsing::getStringFromArgNb(str, 2), "Me");
	cr_assert_eq(Parsing::getStringFromArgNb(str, 3), "Love");
	cr_assert_eq(Parsing::getStringFromArgNb(str, 4), "Me");
	cr_assert_eq(Parsing::getStringFromArgNb(str, 5), "Make");
	cr_assert_eq(Parsing::getStringFromArgNb(str, 6), "Me");
	cr_assert_eq(Parsing::getStringFromArgNb(str, 7), "Crazy");
}

Test(Parsing, vector_creation)
{
	std::string str(
		"Don't Blame Me Love Me Make Me Crazy\nIf it doesn't you "
		"ain't doin' it right\nLord, save me, my drug is my "
		"baby\nI'll be usin' it for the rest of my life\n");
	auto vec = Parsing::createVectorString(str, '\n');
	cr_assert(vec.size() == 4);
	cr_assert_eq(vec[0], "Don't Blame Me Love Me Make Me Crazy");
	cr_assert_eq(vec[1], "If it doesn't you ain't doin' it right");
	cr_assert_eq(vec[2], "Lord, save me, my drug is my baby");
	cr_assert_eq(vec[3], "I'll be usin' it for the rest of my life");
}
