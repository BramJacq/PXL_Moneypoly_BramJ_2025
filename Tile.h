#pragma once
#include <string>

namespace pxl {
// -------------------------------------------------------------
// VRAAG 3: useful & correct class
// -> Tile is een duidelijke class die één taak heeft: bordvak voorstellen
// -------------------------------------------------------------
class Player; // forward declaration

// -------------------------------------------------------------
// VRAAG 7: correct base class
// VRAAG 8: abstract base class
// -------------------------------------------------------------
class Tile {
public:
    Tile(const std::string& name) : name_(name) {}
    virtual ~Tile() {}

    const std::string& getName() const { return name_; }
    virtual void onLand(Player& p) = 0; // abstract base class
protected:
    // VRAAG 5: encapsulation (private/protected members)
    std::string name_;
};
} // namespace pxl
