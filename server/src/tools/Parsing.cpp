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

void Parsing::fillList(
	std::list<std::string> &list, std::string string, char delim)
{
	int total = std::count(string.begin(), string.end(), delim);

	if (total) {
		while (std::count(string.begin(), string.end(), delim) >= 1) {
			unsigned long i = string.find(delim);
			if (i != std::string::npos) {
				std::string tmp = string.substr(0, i);
				list.push_back(tmp);
				string =
					string.substr(i + 1, string.length());
			}
		}
		if (string.length() > 0) {
			list.push_back(string);
		}
	}
}

void Parsing::fillList(std::list<std::string> &list, const std::string &str,
	const std::string &spacers)
{
	auto offsetpos(std::string::npos);
	std::size_t i(str.find_first_not_of(spacers, 0));

	while (i != std::string::npos && str[i]) {
		offsetpos = str.find_first_of(spacers, i);
		if (offsetpos != std::string::npos) {
			list.push_back(str.substr(i, offsetpos - i));
			i = offsetpos + 1;
		} else {
			list.push_back(str);
			i += str.size();
		}
		i = str.find_first_not_of(spacers, i);
	}
}

} // namespace tools
