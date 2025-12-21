#pragma once
#include <string>
#include <iostream>

namespace pxl {

// Player: represents a player (human or bot).
class Player {
public:
    // default ctor
    Player()
        : name_("Player"), money_(500), pos_(0), human_(false) {}

    // parameterized ctor
    Player(const std::string &name, int money = 500, bool human = false)
        : name_(name), money_(money), pos_(0), human_(human) {}

    // copy ctor
    Player(const Player &other)
        : name_(other.name_), money_(other.money_),
        pos_(other.pos_), human_(other.human_) {}

    // destructor
    ~Player() = default;

    // movement using unsigned char
    inline void move(unsigned char steps, unsigned char boardSize) {
        pos_ = static_cast<unsigned char>((pos_ + steps) % boardSize);
    }

    inline void changeMoney(int delta) { this->money_ += delta; }
    inline bool canBuy(int cost) const { return money_ >= cost; }

    inline const std::string &getName() const { return name_; }
    inline int getMoney() const { return money_; }
    inline unsigned char getPos() const { return pos_; }
    inline bool isHuman() const { return human_; }

    // ✅ THIS WAS MISSING
    inline bool isBankrupt() const { return money_ <= 0; }

    // friend operator for logging/debug
    friend std::ostream &operator<<(std::ostream &os, const Player &p) {
        os << p.name_ << "($" << p.money_ << ")";
        return os;
    }

private:
    std::string name_;
    int money_;
    unsigned char pos_;
    bool human_;
};

} // namespace pxl
