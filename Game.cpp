#include "Game.h"
#include <QString>
#include <cstdlib>

namespace pxl {

Game::Game(QObject *parent)
    : QObject(parent), currentIndex_(0)
{
    // 16 tiles -> perfect for 5x5 border
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
    if (players_.empty()) return false;
    return players_[currentIndex_].isHuman();
}

void Game::movePlayer(Player &p, int rolled)
{
    int boardSize = getBoardSize();
    if (boardSize == 0) return;

    unsigned char steps = static_cast<unsigned char>(rolled);
    unsigned char sz = static_cast<unsigned char>(boardSize);

    p.move(steps, sz);
    board_[p.getPos()]->onLand(p);
}

void Game::humanRollOnce()
{
    if (players_.empty()) return;

    Player &p = players_[currentIndex_];
    if (!p.isHuman()) return;

    int roll = (std::rand() % 6) + 1;

    // ✅ ONLY show human roll
    emit message(QString::fromStdString(p.getName()) +
                 " rolled " + QString::number(roll));

    movePlayer(p, roll);
    emit boardChanged();

    advanceOneTurn();
}

void Game::advanceOneTurn()
{
    currentIndex_ = (currentIndex_ + 1) % players_.size();

    if (!isCurrentPlayerHuman()) {
        rollDiceForBots();
    }
}

void Game::rollDiceForBots()
{
    // bots move automatically, NO UI messages
    while (!isCurrentPlayerHuman()) {
        Player &b = players_[currentIndex_];

        int roll = (std::rand() % 6) + 1;
        movePlayer(b, roll);
        emit boardChanged();

        currentIndex_ = (currentIndex_ + 1) % players_.size();
    }
}

} // namespace pxl
