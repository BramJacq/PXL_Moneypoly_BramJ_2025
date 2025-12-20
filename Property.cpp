#include "Property.h"
#include <QString>

namespace pxl {

void Property::onLand(Player &p) {
    if (!owner_) {
        if (p.canBuy(price_)) {
            p.changeMoney(-price_);
            owner_ = &p;
        }
    } else if (owner_ != &p && owner_->isAlive()) {
        int rent = price_ / 5;
        p.changeMoney(-rent);
        owner_->changeMoney(rent);
    }
}

} // namespace pxl
