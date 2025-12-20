#pragma once
#include <string>
#include "Player.h"

namespace pxl {

class Tile {
public:
    Tile(const std::string &name) : name_(name) {}
    virtual ~Tile() = default;

    virtual void onLand(Player &p) = 0;   // abstract
    const std::string &getName() const { return name_; }

protected:
    std::string name_;
};


// ------------------------------------------------------------
//  ConcreteTile: gewone vakjes (Start, DebugPad, etc.)
// ------------------------------------------------------------
class ConcreteTile : public Tile {
public:
    ConcreteTile(const std::string &name)
        : Tile(name) {}

    void onLand(Player &p) override {
        // standaard: geen effect
        (void)p;
    }
};

} // namespace pxl
