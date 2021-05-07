#include <stdlib.h>
#include <string>
using namespace std;

#include "gamefield.h"

enum gameState {
  GAME_IDLE, // in menu, doing nothing
  GAME_RUNNING, // running simulation
  GAME_STOPPED, // simulation stopped (via user or automatically)
  GAME_PREPARED, // startState loaded, ready to start
};

class Game {
  public:
    Game();
    void startSimulation();
    void stopSimulation();
    void loadFromFile(char*);
    void saveToFile(char*);
    gameState getCurrentState();
    void generateGameField(int, int);

  private:
    gameState currentState;


};