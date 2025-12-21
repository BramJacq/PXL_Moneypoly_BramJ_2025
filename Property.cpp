#include "Property.h"
#include <iostream>
#include <cstdlib>

namespace pxl {

void Property::onLand(Player &p) {
    // If unowned, try to buy
    if (!owner_) {
        if (p.canBuy(price_) && (rand() % 2 == 0)) {
            p.changeMoney(-price_);
            owner_ = &p;
            std::cout << p.getName() << " bought " << name_
                      << " for " << price_ << std::endl;
        }
    }
    // If owned by someone else AND owner not bankrupt → pay rent
    else if (owner_ != &p && !owner_->isBankrupt()) {
        int rent = price_ / 5;
        p.changeMoney(-rent);
        owner_->changeMoney(rent);

        std::cout << p.getName() << " paid rent " << rent
                  << " to " << owner_->getName() << std::endl;
    }
}

} // namespace pxl
