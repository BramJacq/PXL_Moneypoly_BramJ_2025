#pragma once
#include <QObject>    // vraag 42: Qt class
#include <vector>    // vraag 36: container
#include <memory>
#include "Player.h"
#include "Tile.h"
#include "Property.h"

namespace pxl {      // vraag 27

class Game : public QObject {
    Q_OBJECT         // vraag 43: signals/slots
public:
    explicit Game(QObject *parent = nullptr);
    // vraag 12: default constructor
    // vraag 16: member initialization list

    void addPlayer(const std::string &name, bool human = false);
    // vraag 21: default values in function definition
    // vraag 29: const reference variable

    void humanRollOnce();
    void advanceOneTurn();
    void endGameNow();

    bool isCurrentPlayerHuman() const;  // vraag 30: const function
    bool isGameOver() const { return gameOver_; } // vraag 31: useful bool

    size_t playerCount() const { return players_.size(); }
    const Player &playerAt(size_t i) const { return players_.at(i); }
    // vraag 29 & 30: const reference

    const Tile &tileAt(size_t i) const { return *board_.at(i); }
    int getBoardSize() const { return static_cast<int>(board_.size()); }

signals:
    void boardChanged();      // vraag 43
    void message(QString txt);

private:
    void movePlayer(Player &p, int rolled); // vraag 34: modern call-by-reference
    void rollDiceForBots();

    int nextAliveIndex(int start) const;
    int aliveCount() const;
    int findWinnerIndex() const;
    void checkGameOver();

    std::vector<Player> players_;                    // vraag 36
    std::vector<std::unique_ptr<Tile>> board_;       // vraag 18: polymorphism

    int currentIndex_;
    bool gameOver_;                                  // vraag 31: useful bool
};

} // namespace pxl
