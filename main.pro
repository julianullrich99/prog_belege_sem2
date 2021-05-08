# work-around for QTBUG-13496
CONFIG += no_batch

QT += gui widgets concurrent core

HEADERS += window.h helper.h game.h gamefield.h gamestate.h cellstate.h fieldwindow.h renderarea.h fileservice.h
SOURCES += main.cpp window.cpp helper.cpp game.cpp gamefield.cpp fieldwindow.cpp renderarea.cpp fileservice.cpp
