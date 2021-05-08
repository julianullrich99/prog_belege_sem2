#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include <string>
#include <QtConcurrent>
using namespace std;

#include "gamefield.h"
#include "gamestate.h"

#include "window.h"

class Window;
class Gamefield;

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
    void showControls();

  private:
    gameState currentState;
    Window *controlWindow;
    Gamefield *gamefield;


};

#endif