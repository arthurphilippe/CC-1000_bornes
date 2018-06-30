/*
** EPITECH PROJECT, 2018
** graphics
** File description:
** Parsing
*/

#include "Parsing.hpp"
#include <algorithm>
#include <iostream>

namespace tools {

std::string Parsing::extractFirstString(std::string &string, char delim)
{
	int total = std::count(string.begin(), string.end(), delim);
	if (!total) return string;
	std::string tmp;
	tmp = string.substr(0, string.find_first_of(delim));
	string = string.substr(
		string.find_first_of(delim) + 1, string.length());
	return tmp;
}

std::string Parsing::getStringFromArgNb(std::string string, int nb)
{

	int total = std::count(string.begin(), string.end(), ' ');
	if (!total) return string;
	for (int i = 0; i < (total - nb); i++) {
		string = string.substr(0, string.find_last_of(" "));
	}
	string = string.substr(string.find_last_of(" ") + 1, string.length());
	return string;
}

std::vector<std::string> Parsing::createVectorString(
	std::string string, char delim)
{
	int total = std::count(string.begin(), string.end(), delim);
	std::vector<std::string> vec(total);
	std::size_t idx(0);

	if (!total) {
		return vec;
	}
	while (std::count(string.begin(), string.end(), delim) >= 1) {
		unsigned long i = string.find(delim);
		if (i != std::string::npos) {
			std::string tmp = string.substr(0, i);
			vec[idx++] = tmp;
			string = string.substr(i + 1, string.length());
		}
	}
	if (string.length() > 0) {
		vec[idx++] = string;
	}
	return vec;
}

} // namespace tools