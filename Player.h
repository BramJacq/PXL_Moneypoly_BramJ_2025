#pragma once
#include <string>
#include <iostream>

namespace pxl {

class Player {
public:
    Player() : name_("Player"), money_(500), pos_(0), human_(false), alive_(true) {}

    Player(const std::string &name, int money = 500, bool human = false)
        : name_(name), money_(money), pos_(0), human_(human), alive_(true) {}

    Player(const Player &other)
        : name_(other.name_), money_(other.money_), pos_(other.pos_),
        human_(other.human_), alive_(other.alive_) {}

    ~Player() = default;

    inline void move(unsigned char steps, unsigned char boardSize) {
        pos_ = static_cast<unsigned char>((pos_ + steps) % boardSize);
    }

    inline void changeMoney(int delta) {
        money_ += delta;
        if (money_ <= 0) alive_ = false;
    }

    inline bool canBuy(int cost) const { return money_ >= cost; }

    inline const std::string &getName() const { return name_; }
    inline int getMoney() const { return money_; }
    inline unsigned char getPos() const { return pos_; }
    inline bool isHuman() const { return human_; }
    inline bool isAlive() const { return alive_; }

    friend std::ostream &operator<<(std::ostream &os, const Player &p) {
        os << p.name_ << "($" << p.money_ << ")";
        return os;
    }

private:
    std::string name_;
    int money_;
    unsigned char pos_;
    bool human_;
    bool alive_;
};

} // namespace pxl
