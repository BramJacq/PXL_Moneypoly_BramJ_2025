#include "Property.h"
#include <cstdlib>

namespace pxl {

void Property::onLand(Player& p) {
    if(owner_ == nullptr) {
        if(p.canBuy(price_) && (rand() % 2 == 0)) { // 50% kans kopen
            p.changeMoney(-price_);
            owner_ = &p;
            std::cout << p.getName() << " kocht " << name_ << " voor " << price_ << "!\n";
        }
    } else if(owner_ != &p) {
        int rent = price_/5;
        p.changeMoney(-rent);
        owner_->changeMoney(rent);
        std::cout << p.getName() << " betaalt huur " << rent << " aan " << owner_->getName() << "\n";
    }
}

} // namespace pxl
