#pragma once
#include <string>   // vraag 35: string class usage
#include <iostream>

namespace pxl {    // vraag 27

class Player {
public:
    Player()
        : name_("Player"), money_(500), pos_(0), human_(false) {}
    // vraag 12: default constructor
    // vraag 16: member initialization list

    Player(const std::string &name, int money = 500, bool human = false)
        : name_(name), money_(money), pos_(0), human_(human) {}
    // vraag 13: parameterized constructor
    // vraag 21: default values
    // vraag 16

    Player(const Player &other)
        : name_(other.name_), money_(other.money_),
        pos_(other.pos_), human_(other.human_) {}
    // vraag 14: copy constructor

    ~Player() = default; // vraag 15: destructor

    inline void move(unsigned char steps, unsigned char boardSize) {
        pos_ = static_cast<unsigned char>((pos_ + steps) % boardSize);
    }
    // vraag 24: inline function
    // vraag 28: memory efficient unsigned char

    inline void changeMoney(int delta) { this->money_ += delta; }
    // vraag 19: useful usage of this

    inline bool canBuy(int cost) const { return money_ >= cost; }
    inline bool isBankrupt() const { return money_ <= 0; }
    // vraag 31: useful bool

    inline const std::string &getName() const { return name_; }
    // vraag 29: const reference variable
    // vraag 30: const function

    inline int getMoney() const { return money_; }
    inline unsigned char getPos() const { return pos_; }
    inline bool isHuman() const { return human_; }

    friend std::ostream &operator<<(std::ostream &os, const Player &p) {
        os << p.name_ << "($" << p.money_ << ")";
        return os;
    }
    // vraag 26: useful friend function

private:
    std::string name_;   // vraag 22: useful member variable
    int money_;
    unsigned char pos_; // vraag 28
    bool human_;        // vraag 31
};

} // namespace pxl
