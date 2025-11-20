#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Tile.h"
#include "Player.h"

namespace pxl {

class Game {
public:
    Game();
    void addPlayer(const std::string& name);
    void start();

private:
    std::vector<std::unique_ptr<Tile>> board_;
    std::vector<std::unique_ptr<Player>> players_;
};

} // namespace pxl
