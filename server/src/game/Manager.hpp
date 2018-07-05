/*
** EPITECH PROJECT, 2018
** server
** File description:
** Manager
*/

#ifndef MANAGER_HPP_
#define MANAGER_HPP_

#include "game/MilleBornes.hpp"
#include "io/Selector.hpp"
#include "io/hdl/IMsgProcessor.hpp"

namespace game {

class Manager : public io::Selector {
public:
	Manager();
	~Manager();

	virtual void registerHandle(
		std::unique_ptr<io::hdl::IHandle> &hdl) override
	{
		std::cout << "regspe\n";
		if (hdl->getType() == io::hdl::HType::CLIENT) {
			std::cout << "regspe2\n";
			auto *client =
				static_cast<io::hdl::Client *>(hdl.release());
			std::unique_ptr<io::hdl::Client> uniqueClient(client);
			this->registerHandle(uniqueClient);
		} else {
			std::cout << "regspe3\n";
			this->Selector::registerHandle(hdl);
		}
	}
	virtual void registerHandle(std::unique_ptr<io::hdl::Client> &hdl);
	virtual bool run() override { return this->Selector::run(); }
	virtual void loop() override { this->Selector::loop(); }

protected:
	std::list<std::unique_ptr<io::hdl::IHandle>> _despatch;
	std::list<std::shared_ptr<io::hdl::IMsgProcessor>> _processors;
	std::list<std::shared_ptr<MilleBornes>> _waitingGames;
};

} // namespace game

#endif /* !MANAGER_HPP_ */
