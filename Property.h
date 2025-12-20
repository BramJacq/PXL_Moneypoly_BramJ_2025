#pragma once
#include "Tile.h"
#include "Player.h"

namespace pxl {

class Property : public Tile {
public:
    Property() : Tile("Property"), price_(100), owner_(nullptr) {}
    Property(const std::string &name, int price) : Tile(name), price_(price), owner_(nullptr) {}
    Property(const Property &other) : Tile(other), price_(other.price_), owner_(nullptr) {}
    ~Property() override = default;

    void onLand(Player &p) override;

private:
    int price_;
    Player *owner_;
};

} // namespace pxl
