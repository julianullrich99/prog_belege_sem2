#include <QApplication>

#include <iostream>
#include <stdlib.h>
#include <QtWidgets>

#include "helper.h"
#include "game.h"

Helper *Helper::instance = 0;

int main(int argc, char **argv) {

    Helper::enableLogging(true);
    Helper::enableDebug(false);

    QApplication app(argc, argv);

    Game game;

    game.showControls();

    return app.exec();
};
