#include <QApplication>

#include <iostream>
#include <stdlib.h>
#include <QtWidgets>

// #include "window.h"
#include "helper.h"
#include "game.h"

Helper *Helper::instance = 0;

int main(int argc, char **argv) {

    Helper::enableLogging(true);
    Helper::enableDebug(true);

    QApplication app(argc, argv);

    // Window window;
    Game game;

    game.showControls();

    // game.setWindow(&window);
    // window.setGame(&game);

    return app.exec();
};
