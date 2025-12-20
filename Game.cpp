#include "Game.h"
#include <cstdlib>

namespace pxl {

Game::Game(QObject *parent)
    : QObject(parent), currentIndex_(0)
{
    board_.push_back(std::make_unique<ConcreteTile>("Start"));
    board_.push_back(std::make_unique<Property>("C++ Debugger", 120));
    board_.push_back(std::make_unique<Property>("Resistor", 100));
    board_.push_back(std::make_unique<Property>("Capacitor", 140));
    board_.push_back(std::make_unique<Property>("Transistor", 160));
    board_.push_back(std::make_unique<Property>("Compiler", 180));
    board_.push_back(std::make_unique<ConcreteTile>("Lab Floor"));
    board_.push_back(std::make_unique<Property>("Power Supply", 220));
    board_.push_back(std::make_unique<Property>("ALU", 250));
    board_.push_back(std::make_unique<Property>("Binary Gate", 230));
    board_.push_back(std::make_unique<Property>("Oscilloscope", 260));
    board_.push_back(std::make_unique<Property>("Microcontroller", 300));

    // extra tiles to fill rectangle
    board_.push_back(std::make_unique<ConcreteTile>("Corda 3"));
    board_.push_back(std::make_unique<ConcreteTile>("Corda 7"));
    board_.push_back(std::make_unique<ConcreteTile>("Corda Bar"));
    board_.push_back(std::make_unique<ConcreteTile>("Corda Cuisine"));
}

void Game::addPlayer(const std::string &name, bool human) {
    players_.emplace_back(name, 500, human);
}

bool Game::isCurrentPlayerHuman() const {
    return players_[currentIndex_].isHuman();
}

void Game::movePlayer(Player &p, int rolled)
{
    p.move(static_cast<unsigned char>(rolled),
           static_cast<unsigned char>(getBoardSize()));
    board_[p.getPos()]->onLand(p);
}

bool Game::checkGameOver()
{
    int aliveCount = 0;
    Player *lastAlive = nullptr;

    for (auto &p : players_) {
        if (p.isAlive()) {
            aliveCount++;
            lastAlive = &p;
        }
    }

    if (aliveCount <= 1 && lastAlive) {
        if (!lastAlive->isHuman()) {
            emit message("YOU LOST! Winner: " +
                         QString::fromStdString(lastAlive->getName()));
        } else {
            emit message("YOU WON!");
        }
        return true;
    }
    return false;
}

void Game::humanRollOnce()
{
    Player &p = players_[currentIndex_];
    if (!p.isAlive() || !p.isHuman()) return;

    int roll = (std::rand() % 6) + 1;
    emit message(QString::fromStdString(p.getName()) +
                 " rolled " + QString::number(roll));

    movePlayer(p, roll);
    emit boardChanged();

    if (!checkGameOver())
        advanceOneTurn();
}

void Game::advanceOneTurn()
{
    do {
        currentIndex_ = (currentIndex_ + 1) % players_.size();
    } while (!players_[currentIndex_].isAlive());

    if (!isCurrentPlayerHuman()) {
        rollDiceForBots();
    }
}

void Game::rollDiceForBots()
{
    while (!isCurrentPlayerHuman()) {
        Player &b = players_[currentIndex_];
        if (!b.isAlive()) {
            currentIndex_ = (currentIndex_ + 1) % players_.size();
            continue;
        }

        int roll = (std::rand() % 6) + 1;
        movePlayer(b, roll);
        emit boardChanged();

        if (checkGameOver())
            return;

        do {
            currentIndex_ = (currentIndex_ + 1) % players_.size();
        } while (!players_[currentIndex_].isAlive());
    }
}

} // namespace pxl
