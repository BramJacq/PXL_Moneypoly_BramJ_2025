#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Tile.h"
#include "Player.h"

namespace pxl {
// -------------------------------------------------------------
// VRAAG 3 & 6 & 8 → Game gebruikt composition: bevat Players & Tiles
// -------------------------------------------------------------
class Game {
public:
    Game();
    void addPlayer(const std::string& name);
    void start();

private:
    // VRAAG 8: composition → Game BEVAT een bord
    std::vector<std::unique_ptr<Tile>> board_;

    // VRAAG 8: composition → Game BEVAT spelers
    std::vector<std::unique_ptr<Player>> players_;
};

} // namespace pxl
