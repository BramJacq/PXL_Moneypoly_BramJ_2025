#pragma once
#include <vector>
#include <memory>
#include <string>
#include <functional>
#include <QObject>
#include "Tile.h"
#include "Player.h"

namespace pxl {

class Game : public QObject {
    Q_OBJECT
public:
    explicit Game(QObject *parent = nullptr);
    Game(unsigned char boardSize, QObject *parent = nullptr);
    Game(const Game &other);
    ~Game();

    // add a player; default isHuman = false
    void addPlayer(const std::string &name, bool isHuman = false);

    // Called by UI to do *only* the human player's roll and then return.
    // After this call BoardWidget will start the auto-play for bots.
    void humanRollOnce();

    // Called (by UI via QTimer) to advance a single bot turn.
    void advanceOneTurn();

    // Whether current player is human (used by UI to know when to stop auto-stepping)
    bool isCurrentPlayerHuman() const;

    // accessors for UI
    unsigned char boardSize() const { return static_cast<unsigned char>(board_.size()); }
    size_t playerCount() const { return players_.size(); }
    const Player &playerAt(size_t idx) const { return *players_.at(idx); }
    const Tile &tileAt(size_t idx) const { return *board_.at(idx); }

signals:
    void boardChanged();

private:
    std::vector<std::unique_ptr<Tile>> board_;      // composition: Game owns Tiles (Properties)
    std::vector<std::unique_ptr<Player>> players_;  // composition: Game owns Players
    std::vector<bool> isHuman_;                     // parallel vector marking humans
    size_t currentIdx_;                             // index of next player to act

    void initPerimeterBoard(size_t cols, size_t rows); // build perimeter tiles
    void initDefaultBoard(); // fallback
    unsigned char rollDice(); // simulate rolling with thread+lambda (fast)
};

} // namespace pxl
