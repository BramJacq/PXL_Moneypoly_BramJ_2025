#pragma once
#include <string>

namespace pxl {

class Player; // forward declaration

class Tile {
public:
    Tile(const std::string& name) : name_(name) {}
    virtual ~Tile() {}

    const std::string& getName() const { return name_; }
    virtual void onLand(Player& p) = 0; // abstract base class
protected:
    std::string name_;
};

} // namespace pxl
