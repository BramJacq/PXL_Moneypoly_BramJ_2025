#pragma once
#include <QObject>
#include <vector>
#include <memory>
#include "Player.h"
#include "Tile.h"
#include "Property.h"

namespace pxl {

class Game : public QObject {
    Q_OBJECT
public:
    explicit Game(QObject *parent = nullptr);

    void addPlayer(const std::string &name, bool human = false);

    // Called by UI
    void humanRollOnce();
    void advanceOneTurn();

    bool isCurrentPlayerHuman() const;
    size_t playerCount() const { return players_.size(); }
    const Player &playerAt(size_t i) const { return players_.at(i); }

    const Tile &tileAt(size_t i) const { return *board_.at(i); }
    int getBoardSize() const { return static_cast<int>(board_.size()); }

signals:
    void boardChanged();
    void message(QString txt);

private:
    void movePlayer(Player &p, int rolled);
    void rollDiceForBots();

    std::vector<Player> players_;
    std::vector<std::unique_ptr<Tile>> board_;

    int currentIndex_;
};

} // namespace pxl
