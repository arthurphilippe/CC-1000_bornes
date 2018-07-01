/*
** COBRA CODING CLUB PROJECT
** graphics
** File description:
** Parsing
*/

#ifndef PARSERENGINE_HPP_
#define PARSERENGINE_HPP_

#include <list>
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
	static void fillList(
		std::list<std::string> &list, std::string str, char spacer);
	static void fillList(std::list<std::string> &list,
		const std::string &str, const std::string &spacers);
	static std::string extractFirstString(
		std::string &string, char delim = '\n');
};

} // namespace tools

#endif /* !PARSERENGINE_HPP_ */
