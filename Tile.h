#pragma once
#include <string>
#include "Player.h"

namespace pxl {  // vraag 27

class Tile {
public:
    Tile(const std::string &name) : name_(name) {}
    // vraag 13: parameterized constructor

    virtual ~Tile() = default;
    // vraag 15: virtual destructor

    virtual void onLand(Player &p) = 0;
    // vraag 18: polymorphism

    const std::string &getName() const { return name_; }
    // vraag 29 & 30

protected:
    std::string name_;
};

class ConcreteTile : public Tile {
public:
    ConcreteTile(const std::string &name) : Tile(name) {}
    void onLand(Player &) override {}
    // vraag 18: override polymorphism
};

} // namespace pxl
