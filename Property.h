#pragma once
#include "Tile.h"
#include "Player.h"

namespace pxl {   // vraag 27

class Property : public Tile {
public:
    Property() : Tile("Property"), price_(100), owner_(nullptr) {}
    // vraag 12: default constructor
    // vraag 16
    // vraag 37: nullptr usage

    Property(const std::string &name, int price)
        : Tile(name), price_(price), owner_(nullptr) {}
    // vraag 13: parameterized constructor

    Property(const Property &other)
        : Tile(other), price_(other.price_), owner_(nullptr) {}
    // vraag 14: copy constructor

    ~Property() override = default;
    // vraag 15: destructor

    void onLand(Player &p) override;
    // vraag 18: dynamic polymorphism

private:
    int price_;
    Player *owner_;
};

} // namespace pxl
