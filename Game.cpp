#include "Game.h"
#include "Property.h"
#include "Utils.h"
#include <algorithm>
#include <thread>
#include <chrono>
#include <iostream>
#include <cstdlib>

namespace pxl {

Game::Game(QObject *parent)
    : QObject(parent), currentIdx_(0)
{
    // default board: perimeter of 7 columns x 5 rows => perimeter tiles = 24
    initPerimeterBoard(7, 5);
}

Game::Game(unsigned char boardSize, QObject *parent)
    : QObject(parent), currentIdx_(0)
{
    // simplistic: create boardSize tiles linearly (not used in our UI)
    for (unsigned char i = 0; i < boardSize; ++i)
        board_.push_back(std::make_unique<Property>("Tile" + std::to_string(i), 100));
}

Game::Game(const Game &other)
    : QObject(nullptr), currentIdx_(other.currentIdx_)
{
    for (const auto &t : other.board_)
        board_.push_back(std::make_unique<Property>(t->getName(), 100));
    for (const auto &p : other.players_) {
        players_.push_back(std::make_unique<Player>(*p));
        isHuman_.push_back(false);
    }
}

Game::~Game() = default;

void Game::initDefaultBoard() {
    // fallback - create minimal perimeter
    initPerimeterBoard(5, 4);
}

// Build a rectangular perimeter board with cols x rows grid, but only tiles along outer border.
// cols must be >=3, rows >=3 to form a ring.
void Game::initPerimeterBoard(size_t cols, size_t rows) {
    if (cols < 3) cols = 3;
    if (rows < 3) rows = 3;

    // list of theme names (programming + electronics)
    std::vector<std::string> names = {
        "PXL","C++","Elektronica","PSOC","Raspberry",
        "Spoel","Weerstand","Diode","Triode","Condensator",
        "Transistor","Breadboard","Sensor","Micro","Kernel",
        "Firmware","GPIO","UART","I2C","SPI","Voltage",
        "Capacitor","Resistor","Inductor","LED","ADC"
    };

    board_.clear();

    // Helper lambda to push a Property name (cycle names if necessary)
    size_t nameIndex = 0;
    auto pushName = [&](const std::string &n) {
        board_.push_back(std::make_unique<Property>(n, 100));
    };
    auto nextName = [&](){
        const std::string &n = names[nameIndex % names.size()];
        ++nameIndex;
        return n;
    };

    // Top row: left -> right
    for (size_t c = 0; c < cols; ++c) pushName(nextName());
    // Right column: top+1 -> bottom-1
    for (size_t r = 1; r + 1 < rows; ++r) pushName(nextName());
    // Bottom row: right -> left
    for (size_t c = 0; c < cols; ++c) pushName(nextName());
    // Left column: bottom-1 -> top+1
    for (size_t r = 1; r + 1 < rows; ++r) pushName(nextName());

    // shuffle board slightly for variety
    std::random_shuffle(board_.begin(), board_.end());
}

void Game::addPlayer(const std::string &name, bool isHuman) {
    players_.push_back(std::make_unique<Player>(name, 500, isHuman));
    isHuman_.push_back(isHuman);
    emit boardChanged();
}

unsigned char Game::rollDice() {
    unsigned char result = 0;
    std::thread t([&result](){
        for (int i = 0; i < 6; ++i) {
            result = static_cast<unsigned char>((rand() % 6) + 1);
            std::this_thread::sleep_for(std::chrono::milliseconds(30));
        }
    });
    t.join();
    return result;
}

// Called by UI when human clicked Roll. This function will perform the current player's turn
// only if the current player is human. After humanRollOnce returns, the caller (BoardWidget) will
// start a QTimer to call advanceOneTurn() repeatedly to let bots play.
void Game::humanRollOnce() {
    if (players_.empty()) return;
    if (currentIdx_ >= players_.size()) currentIdx_ = 0;

    if (!isHuman_[currentIdx_]) {
        // if it's not human's turn, do nothing
        return;
    }

    Player &p = *players_[currentIdx_];
    unsigned char roll = rollDice();
    p.move(roll, static_cast<unsigned char>(board_.size()));
    // call tile effect
    board_[p.getPos()]->onLand(p);
    p.changeMoney(10);

    // advance to next (bots)
    currentIdx_ = (currentIdx_ + 1) % players_.size();

    emit boardChanged();
}

// Advance a single turn (used for bots). If it encounters a human, it returns without acting.
// Returns true if it stepped (i.e., performed a bot turn), false if it reached a human (nothing done).
void Game::advanceOneTurn() {
    if (players_.empty()) return;
    // if current is human, do nothing
    if (isHuman_[currentIdx_]) {
        // nothing to do; UI should stop the timer
        return;
    }

    // bot's turn
    Player &p = *players_[currentIdx_];
    unsigned char roll = rollDice();
    p.move(roll, static_cast<unsigned char>(board_.size()));
    board_[p.getPos()]->onLand(p);
    p.changeMoney(10);

    // advance
    currentIdx_ = (currentIdx_ + 1) % players_.size();

    emit boardChanged();
}

bool Game::isCurrentPlayerHuman() const {
    if (players_.empty()) return false;
    if (currentIdx_ >= isHuman_.size()) return false;
    return isHuman_[currentIdx_];
}

} // namespace pxl
