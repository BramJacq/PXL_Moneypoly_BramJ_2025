#pragma once
#include <string>

namespace pxl {
// -------------------------------------------------------------
// Player class
// VRAAG 3: correct class → Player bevat alle speler-data
// VRAAG 5: encapsulation → alles private
// -------------------------------------------------------------
class Player {
public:
    Player(const std::string& name, int money = 500)
        : name_(name), money_(money), pos_(0) {}

    void move(int steps, int boardSize) { pos_ = (pos_ + steps) % boardSize; }
    void changeMoney(int delta) { money_ += delta; }
    bool canBuy(int cost) const { return money_ >= cost; }
    bool isBankrupt() const { return money_ <= 0; }

    int getPos() const { return pos_; }
    int getMoney() const { return money_; }
    const std::string& getName() const { return name_; }

private:
    std::string name_;
    int money_;
    int pos_;
};

} // namespace pxl
