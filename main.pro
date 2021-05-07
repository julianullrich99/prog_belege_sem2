# work-around for QTBUG-13496
CONFIG += no_batch

QT += gui widgets

HEADERS += window.h helper.h game.h gamefield.h
SOURCES += main.cpp window.cpp helper.cpp game.cpp gamefield.cpp
