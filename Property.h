#pragma once
#include "Tile.h"
#include "Player.h"

namespace pxl {

// Property tile: buyable tile that charges rent.
class Property : public Tile {
public:
    // default ctor
    Property() : Tile("Property"), price_(100), owner_(nullptr) {}

    // parameterized ctor
    Property(const std::string &name, int price) : Tile(name), price_(price), owner_(nullptr) {}

    // copy ctor: owner_ reset to nullptr for new copy
    Property(const Property &other) : Tile(other), price_(other.price_), owner_(nullptr) {}

    ~Property() override = default;

    void onLand(Player &p) override;

    int getPrice() const { return price_; }
    bool isOwned() const { return owner_ != nullptr; }
    const Player* owner() const { return owner_; }

private:
    int price_;
    Player *owner_; // non-owning pointer to a Player (managed by Game)
};

} // namespace pxl
