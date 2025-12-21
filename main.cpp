#include <QApplication>  // vraag 42: Qt
#include <ctime>
#include <cstdlib>
#include "BoardWidget.h"
#include "Game.h"

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    // vraag 2: clean main (only setup & run)

    srand(static_cast<unsigned int>(time(nullptr)));

    pxl::Game game; // vraag 12: default constructor

    game.addPlayer("Bram", true);
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
