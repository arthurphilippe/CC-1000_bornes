/*
** EPITECH PROJECT, 2018
** server
** File description:
** IMsgProcessor
*/

#ifndef IMSGPROCESSOR_HPP_
#define IMSGPROCESSOR_HPP_

namespace io::hdl {

class Client;

class IMsgProcessor {
public:
	virtual ~IMsgProcessor() = default;
	virtual void processMsg(Client &handle, const std::string &msg) = 0;
	virtual bool live() = 0;
};

} // namespace io::hdl

#endif /* !IMSGPROCESSOR_HPP_ */