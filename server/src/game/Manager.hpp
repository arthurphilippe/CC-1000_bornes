/*
** EPITECH PROJECT, 2018
** server
** File description:
** Manager
*/

#ifndef MANAGER_HPP_
#define MANAGER_HPP_

#include <chrono>
#include "game/MilleBornes.hpp"
#include "io/Selector.hpp"
#include "io/hdl/IMsgProcessor.hpp"

namespace game {

class Manager : public io::Selector {
public:
	Manager();
	~Manager();

	virtual void registerHandle(
		std::unique_ptr<io::hdl::IHandle> &hdl) override;
	virtual void registerHandle(std::unique_ptr<io::hdl::Client> &hdl);
	virtual bool run() override;
	virtual void loop() override { this->Selector::loop(); }

protected:
	struct WaitingGame {
		std::shared_ptr<io::hdl::IMsgProcessor> game;
		MilleBornes *gameptr;
		std::chrono::system_clock::time_point tp;
	};
	std::list<std::shared_ptr<io::hdl::IMsgProcessor>> _processors;
	std::list<WaitingGame> _waitingGames;
};

} // namespace game

#endif /* !MANAGER_HPP_ */
