#pragma once
#include "Tile.h"
#include "Player.h"
#include <iostream>

namespace pxl {
// -------------------------------------------------------------
// VRAAG 4: abstraction → Property verbergt interne logica
// VRAAG 6: inheritance → Property erft van Tile
// VRAAG 5: encapsulation → private data price_ en owner_
// -------------------------------------------------------------
class Property : public Tile {
public:
    Property(const std::string& name, int price)
        : Tile(name), price_(price), owner_(nullptr) {}

    void onLand(Player& p) override;

private:
    int price_;
    Player* owner_;
};

} // namespace pxl
