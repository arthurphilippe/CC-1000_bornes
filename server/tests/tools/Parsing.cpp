/*
** COBRA CODING CLUB PROJECT
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
	cr_expect_eq(Parsing::getStringFromArgNb(str, 0), "Don't");
	cr_expect_eq(Parsing::getStringFromArgNb(str, 1), "Blame");
	cr_expect_eq(Parsing::getStringFromArgNb(str, 2), "Me");
	cr_expect_eq(Parsing::getStringFromArgNb(str, 3), "Love");
	cr_expect_eq(Parsing::getStringFromArgNb(str, 4), "Me");
	cr_expect_eq(Parsing::getStringFromArgNb(str, 5), "Make");
	cr_expect_eq(Parsing::getStringFromArgNb(str, 6), "Me");
	cr_expect_eq(Parsing::getStringFromArgNb(str, 7), "Crazy");
}

Test(Parsing, vector_creation)
{
	std::string str(
		"Don't Blame Me Love Me Make Me Crazy\nIf it doesn't you "
		"ain't doin' it right\nLord, save me, my drug is my "
		"baby\nI'll be usin' it for the rest of my life\n");
	auto vec = Parsing::createVectorString(str, '\n');
	cr_expect(vec.size() == 4);
	cr_expect_eq(vec[0], "Don't Blame Me Love Me Make Me Crazy");
	cr_expect_eq(vec[1], "If it doesn't you ain't doin' it right");
	cr_expect_eq(vec[2], "Lord, save me, my drug is my baby");
	cr_expect_eq(vec[3], "I'll be usin' it for the rest of my life");
}

Test(Parsing, list_filling)
{
	std::list<std::string> substrs;
	substrs.push_back("patate");
	std::string str(
		"Don't Blame Me Love Me Make Me Crazy\nIf it doesn't you "
		"ain't doin' it right\nLord, save me, my drug is my "
		"baby\nI'll be usin' it for the rest of my life\n");
	Parsing::fillList(substrs, str, '\n');
	cr_expect(substrs.size() == 5);
	cr_assert_not(substrs.empty());
	cr_expect_eq(substrs.front(), "patate");
	substrs.pop_front();
	cr_assert_not(substrs.empty());
	cr_expect_eq(substrs.front(), "Don't Blame Me Love Me Make Me Crazy");
	substrs.pop_front();
	cr_expect_eq(
		substrs.front(), "If it doesn't you ain't doin' it right");
	substrs.pop_front();
	cr_assert_not(substrs.empty());
	cr_expect_eq(substrs.front(), "Lord, save me, my drug is my baby");
	substrs.pop_front();
	cr_expect_eq(
		substrs.front(), "I'll be usin' it for the rest of my life");
}

Test(Parsing, list_filling_multi)
{
	std::list<std::string> substrs;
	substrs.push_back("patate");
	std::string str("\nFirst\nSecond\nThird\n\r\nFourth\nFifth\n\n");
	Parsing::fillList(substrs, str, std::string{"\n\r"});
	cr_expect(substrs.size() == 6, "size is %ld", substrs.size());
	cr_assert_not(substrs.empty());
	cr_expect_eq(substrs.front(), "patate");
	substrs.pop_front();
	cr_assert_not(substrs.empty());
	cr_expect_eq(substrs.front(), "First");
	substrs.pop_front();
	cr_assert_not(substrs.empty());
	cr_expect_eq(substrs.front(), "Second");
	substrs.pop_front();
	cr_assert_not(substrs.empty());
	cr_expect_eq(substrs.front(), "Third");
	substrs.pop_front();
	cr_assert_not(substrs.empty());
	cr_expect_eq(substrs.front(), "Fourth");
	substrs.pop_front();
	cr_assert_not(substrs.empty());
	cr_expect_eq(substrs.front(), "Fifth");
}

Test(Parsing, list_filling_multi_whole)
{
	std::list<std::string> substrs;
	substrs.push_back("patate");
	std::string str("voiture");
	Parsing::fillList(substrs, str, std::string{"\n\r"});
	cr_expect(substrs.size() == 2, "size is %ld", substrs.size());
	cr_assert_not(substrs.empty());
	cr_expect_eq(substrs.back(), "voiture");
}
