#include "Game.h"
#include <cstdlib>
#include <ctime>

int main() {
    srand(time(nullptr)); // echte random

    pxl::Game g;
    g.addPlayer("Martijn");
    g.addPlayer("Bram");
    g.addPlayer("Joel");
    g.addPlayer("Ward");
    g.addPlayer("Kaelig");
    g.addPlayer("Jonas");
    g.addPlayer("Fe");
    g.addPlayer("Maciej");
    g.addPlayer("Viktor");
    g.addPlayer("Timo");
    g.addPlayer("Fee");
    g.addPlayer("Lennert");
    g.addPlayer("Johnny");

    g.start();
}
