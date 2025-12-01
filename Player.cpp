#include "Player.h"
#include <iostream>

namespace pxl {

Player::Player()
    : name_("Unknown"), money_(1500), position_(0)
{
}

Player::Player(const std::string& name)
    : name_(name), money_(1500), position_(0)
{
}

Player::Player(const Player& other)
    : name_(other.name_),
      money_(other.money_),
      position_(other.position_)
{
}

Player::~Player() = default;

void Player::move(int steps, int boardSize)
{
    position_ = (position_ + steps) % boardSize;
}

void Player::changeMoney(int amount)
{
    money_ += amount;
}

bool Player::canAfford(int price) const
{
    return money_ >= price;
}

void Player::printStatus() const
{
    std::cout << name_ << " | Money: " << money_
              << " | Position: " << position_ << std::endl;
}

} // namespace pxl
