#pragma once
#include <string>
#include "Player.h"

namespace pxl {

class Tile {
public:
    Tile(const std::string &name) : name_(name) {}
    virtual ~Tile() = default;

    virtual void onLand(Player &p) = 0;
    const std::string &getName() const { return name_; }

protected:
    std::string name_;
};

class ConcreteTile : public Tile {
public:
    ConcreteTile(const std::string &name) : Tile(name) {}
    void onLand(Player &) override {}
};

} // namespace pxl
