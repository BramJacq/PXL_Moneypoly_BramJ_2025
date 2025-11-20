#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <cstdlib>
#include <ctime>
#include <algorithm>

namespace pxl {

// ---------- ABSTRACT TILE ----------
class Player;

class Tile {
public:
    Tile(const std::string& name) : name_(name) {}
    virtual ~Tile() {}

    const std::string& getName() const { return name_; }
    virtual void onLand(Player& p) = 0;

protected:
    std::string name_;
};

// ---------- PROPERTY ----------
class Property : public Tile {
public:
    Property(const std::string& name, int price)
        : Tile(name), price_(price), owner_(nullptr) {}

    void onLand(Player& p) override;

private:
    int price_;
    Player* owner_;
};

// ---------- PLAYER ----------
class Player {
public:
    Player(const std::string& name, int money = 500)
        : name_(name), money_(money), position_(0) {}

    void changeMoney(int d) { money_ += d; }
    bool canBuy(int cost) const { return money_ >= cost; }
    void move(int steps, int boardSize) {
        position_ = (position_ + steps) % boardSize;
    }

    int getMoney() const { return money_; }
    int getPos() const { return position_; }
    const std::string& getName() const { return name_; }

private:
    std::string name_;
    int money_;
    int position_;
};

// ---- Property land behavior ----
void Property::onLand(Player& p)
{
    if (owner_ == nullptr) {
        // 50% kans om te kopen → betere balans
        if (p.canBuy(price_) && (rand() % 2 == 0)) {
            p.changeMoney(-price_);
            owner_ = &p;
            std::cout << p.getName() << " kocht " << name_
                      << " voor " << price_ << "!\n";
        }
    } else if (owner_ != &p) {
        int rent = price_ / 5;
        p.changeMoney(-rent);
        owner_->changeMoney(rent);
        std::cout << p.getName() << " betaalt huur (" << rent
                  << ") aan " << owner_->getName() << ".\n";
    }
}

// ---------- GAME ----------
class Game {
public:
    Game() {
        std::vector<std::string> names = {
            "PXL","C++","Elektronica","PSOC","Raspberry",
            "Spoel","Weerstand","Diode","Triode","Condensator"
        };
        for (auto& n : names)
            board_.push_back(std::make_unique<Property>(n, 100));

        // shuffle bord → eerlijk spel
        std::random_shuffle(board_.begin(), board_.end());
    }

    void addPlayer(const std::string& n) {
        players_.push_back(std::make_unique<Player>(n));
    }

    void start() {
        std::cout << "PXL Monopoly Lite Start!\n";

        while (true) {
            for (auto& p : players_) {

                int roll = (rand() % 6) + 1;
                p->move(roll, board_.size());

                std::cout << "\n" << p->getName()
                          << " rolt " << roll << " en landt op "
                          << board_[p->getPos()]->getName() << "\n";

                board_[p->getPos()]->onLand(*p);

                // klein inkomstenbonus
                p->changeMoney(+10);

                std::cout << p->getName() << " heeft nu "
                          << p->getMoney() << " geld.\n";

                if (p->getMoney() <= 0) {
                    std::cout << p->getName()
                    << " is failliet! Game over.\n";
                    return;
                }
            }
        }
    }

private:
    std::vector<std::unique_ptr<Tile>> board_;
    std::vector<std::unique_ptr<Player>> players_;
};

} // namespace pxl


// ---------- MAIN ----------
int main()
{
    using namespace pxl;

    srand(time(nullptr));   // <<< BELANGRIJK voor echte random

    Game g;
    g.addPlayer("Martijn");
    g.addPlayer("Bram");
    g.addPlayer("Maciej");
    g.addPlayer("Viktor");
    g.addPlayer("Timo");
    g.addPlayer("Fee");
    g.addPlayer("Jonas");
    g.addPlayer("Fe");
    g.addPlayer("Ward");
    g.addPlayer("Joel");
    g.addPlayer("Kaelig");

    g.start();
}
