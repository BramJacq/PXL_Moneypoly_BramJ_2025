#include "Game.h"
#include <QString>
#include <cstdlib>

namespace pxl {

Game::Game(QObject *parent)
    : QObject(parent), currentIndex_(0), gameOver_(false)
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
    if (players_.empty()) return false;
    return players_[currentIndex_].isHuman();
}

int Game::aliveCount() const {
    int count = 0;
    for (const auto &p : players_) {
        if (!p.isBankrupt()) count++;
    }
    return count;
}

int Game::findWinnerIndex() const {
    for (size_t i = 0; i < players_.size(); ++i) {
        if (!players_[i].isBankrupt())
            return static_cast<int>(i);
    }
    return -1;
}

int Game::nextAliveIndex(int start) const {
    int idx = start;
    int size = static_cast<int>(players_.size());

    do {
        idx = (idx + 1) % size;
    } while (players_[idx].isBankrupt());

    return idx;
}

void Game::checkGameOver()
{
    if (gameOver_) return;

    if (aliveCount() <= 1) {
        int winIdx = findWinnerIndex();
        if (winIdx >= 0) {
            emit message(QString::fromStdString(players_[winIdx].getName()) + " WON!");
        }
        gameOver_ = true;
    }
}

void Game::movePlayer(Player &p, int rolled)
{
    int boardSize = getBoardSize();
    if (boardSize == 0) return;

    unsigned char steps = static_cast<unsigned char>(rolled);
    unsigned char sz = static_cast<unsigned char>(boardSize);

    p.move(steps, sz);
    board_[p.getPos()]->onLand(p);

    if (p.isBankrupt()) {
        emit message(QString::fromStdString(p.getName()) + " is bankrupt!");
    }
}

void Game::humanRollOnce()
{
    if (players_.empty() || gameOver_) return;

    Player &p = players_[currentIndex_];
    if (!p.isHuman() || p.isBankrupt()) return;

    int roll = (std::rand() % 6) + 1;

    emit message(QString::fromStdString(p.getName()) +
                 " rolled " + QString::number(roll));

    movePlayer(p, roll);
    emit boardChanged();

    if (p.isBankrupt()) {
        emit message("YOU LOST!");
        int winIdx = findWinnerIndex();
        if (winIdx >= 0) {
            emit message(QString::fromStdString(players_[winIdx].getName()) + " WON!");
        }
        gameOver_ = true;
        return;
    }

    checkGameOver();
    advanceOneTurn();
}

void Game::advanceOneTurn()
{
    if (gameOver_) return;

    currentIndex_ = nextAliveIndex(currentIndex_);

    if (!isCurrentPlayerHuman()) {
        rollDiceForBots();
    }
}

void Game::rollDiceForBots()
{
    while (!gameOver_ && !isCurrentPlayerHuman()) {
        Player &b = players_[currentIndex_];
        if (b.isBankrupt()) {
            currentIndex_ = nextAliveIndex(currentIndex_);
            continue;
        }

        int roll = (std::rand() % 6) + 1;

        emit message(QString::fromStdString(b.getName()) +
                     " rolled " + QString::number(roll));

        movePlayer(b, roll);
        emit boardChanged();

        checkGameOver();
        if (gameOver_) return;

        currentIndex_ = nextAliveIndex(currentIndex_);
    }
}

void Game::endGameNow()
{
    if (gameOver_) return;

    int richest = -1;
    int maxMoney = -999999;

    for (size_t i = 0; i < players_.size(); ++i) {
        if (!players_[i].isBankrupt() && players_[i].getMoney() > maxMoney) {
            maxMoney = players_[i].getMoney();
            richest = static_cast<int>(i);
        }
    }

    if (richest >= 0) {
        emit message(QString::fromStdString(players_[richest].getName()) + " WON!");
    }

    gameOver_ = true;
}

} // namespace pxl
