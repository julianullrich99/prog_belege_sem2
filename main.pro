# work-around for QTBUG-13496
CONFIG += no_batch

QT += gui widgets concurrent

HEADERS += window.h helper.h game.h gamefield.h gamestate.h cellstate.h fieldwindow.h renderarea.h
SOURCES += main.cpp window.cpp helper.cpp game.cpp gamefield.cpp fieldwindow.cpp renderarea.cpp
