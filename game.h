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

class Game {
  public:
    Game();
    void startSimulation();
    void stopSimulation();
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

  private:
    gameState currentState;
    Window *controlWindow;
    Gamefield *gamefield;
    Fieldwindow *fieldwindow;

};

#endif