#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include <string>
#include <QtConcurrent>
#include <QObject>
using namespace std;

#include "gamefield.h"
#include "gamestate.h"
#include "fieldwindow.h"
#include "window.h"

class Window;
class Gamefield;
class Fieldwindow;
class QTimer;

class Game {
  public:
    Game();
    void loadFromFile(char*);
    void saveToFile(char*);
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

  private:
    gameState currentState;
    Window *controlWindow;
    Gamefield *gamefield;
    Fieldwindow *fieldwindow;

    int simulationSpeed = 100;
    QTimer *simulationTimer;

};

#endif