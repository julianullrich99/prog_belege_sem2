#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include <string>
#include <QtConcurrent>
#include <QObject>
#include <QDialog>
using namespace std;

#include "gamefield.h"
#include "gamestate.h"
#include "fieldwindow.h"
#include "window.h"
#include "fileservice.h"

class Window;
class Gamefield;
class Fieldwindow;
class QTimer;
class Fileservice;

class Game {
  public:
    Game();
    void loadFromFile();
    void saveToFile();
    gameState getCurrentState();
    void generateGameField(int sizeX, int sizeY, int fill);
    void setState(gameState);
    void setWindow(Window*);
    Window* getWindow();
    void showControls();
    void showFieldwindow();
    void stepNextGeneration();
    void clearFieldwindow();
    void setSimulationSpeed(int time);
    void handleTimerEvent();
    void startSimulation();
    void pauseSimulation();
    Fieldwindow* getFieldwindow();
    void enableEditGamefield(bool);
    Gamefield* generateEmptyGamefield(int sizeX, int sizeY);
    Gamefield* getGamefield();

  private:
    gameState currentState;
    Window *controlWindow;
    Gamefield *gamefield;
    Fieldwindow *fieldwindow;
    Fileservice *fileservice;

    int simulationSpeed = 100;
    QTimer *simulationTimer;

};

#endif