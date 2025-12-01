#pragma once
#include <string>

namespace pxl {

class Player; // forward

// Abstract base class for board tiles.
class Tile {
public:
    Tile() : name_("Tile") {}
    Tile(const std::string &name) : name_(name) {}
    Tile(const Tile &other) = default;
    virtual ~Tile() = default;

    const std::string &getName() const { return name_; }

    // pure virtual, must be overridden
    virtual void onLand(Player &p) = 0;

protected:
    std::string name_;
};

} // namespace pxl
