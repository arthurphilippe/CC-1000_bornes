/*
** EPITECH PROJECT, 2018
** graphics
** File description:
** Parsing
*/

#ifndef PARSERENGINE_HPP_
#define PARSERENGINE_HPP_

#include <string>
#include <vector>

namespace tools {
class Parsing {
public:
	Parsing() = delete;
	~Parsing() = delete;
	static std::string getStringFromArgNb(std::string string, int nb);
	static std::vector<std::string> createVectorString(
		std::string string, char delim);
	static std::string extractFirstString(
		std::string &string, char delim = '\n');

protected:
private:
};
} // namespace tools

#endif /* !PARSERENGINE_HPP_ */
