#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include <string>
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

    void setWindow(Window*);
    void showControls();

  private:
    void setState(gameState);
    gameState currentState;
    Window *controlWindow;
    Gamefield *gamefield;


};

#endif