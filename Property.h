#pragma once
#include "Tile.h"
#include "Player.h"
#include <iostream>

namespace pxl {

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
