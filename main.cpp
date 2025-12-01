#include <QApplication>
#include <ctime>
#include <cstdlib>
#include "BoardWidget.h"
#include "Game.h"

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    srand(static_cast<unsigned int>(time(nullptr)));

    pxl::Game game;

    // Bram = human
    game.addPlayer("Bram", true);

    // bots
    game.addPlayer("Martijn");
    game.addPlayer("Joel");
    game.addPlayer("Ward");
    game.addPlayer("Kaelig");
    game.addPlayer("Jonas");
    game.addPlayer("Fe");
    game.addPlayer("Maciej");
    game.addPlayer("Viktor");
    game.addPlayer("Timo");
    game.addPlayer("Fee");
    game.addPlayer("Lennert");
    game.addPlayer("Johnny");

    pxl::BoardWidget w(&game);
    w.show();

    return app.exec();
}
