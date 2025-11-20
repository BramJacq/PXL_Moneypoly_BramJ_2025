#include "Game.h"
#include "Property.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>

namespace pxl {

Game::Game() {
    std::vector<std::string> names = {
        "PXL","C++","Elektronica","PSOC","Raspberry",
        "Spoel","Weerstand","Diode","Triode","Condensator"
    };
    for(auto& n : names)
        board_.push_back(std::make_unique<Property>(n,100));

    std::random_shuffle(board_.begin(), board_.end());
}

void Game::addPlayer(const std::string& name) {
    players_.push_back(std::make_unique<Player>(name));
}

void Game::start() {
    std::cout << "PXL Monopoly Start!\n";

    while(true) {
        for(auto& p : players_) {
            int roll = (rand() % 6) + 1;
            p->move(roll, board_.size());

            std::cout << p->getName() << " rolt " << roll
                      << " en landt op " << board_[p->getPos()]->getName() << "\n";

            board_[p->getPos()]->onLand(*p);

            p->changeMoney(10); // kleine bonus
            std::cout << p->getName() << " heeft nu " << p->getMoney() << "\n";

            if(p->isBankrupt()) {
                std::cout << p->getName() << " is failliet! Game over.\n";
                return;
            }
        }
    }
}

} // namespace pxl
