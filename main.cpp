#include <QApplication>

#include <iostream>
#include <stdlib.h>
#include <QtWidgets>

#include "window.h"
#include "helper.h"
#include "game.h"

Helper *Helper::instance = 0;

int main(int argc, char **argv)
{
    Helper::enableLogging(true);

    QApplication app(argc, argv);

    Game game;

    Window window;
    window.show();

    return app.exec();
};
