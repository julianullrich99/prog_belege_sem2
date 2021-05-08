#include "game.h"
#include "helper.h"
// #include "window.h"

#include <stdlib.h>
#include <string>
#include <iostream>

using namespace std;

Game::Game() {
  currentState = GAME_IDLE;
  controlWindow = new Window();
  controlWindow->setGameContainer(this);

  gamefield = nullptr;
}

void Game::showControls() {
  controlWindow->show();
  controlWindow->changeGameStateDisplay(currentState);
}

void Game::setState(gameState state) {
  currentState = state;
  controlWindow->changeGameStateDisplay(state);
}

void Game::generateGameField(int sizeX, int sizeY, int fill) {
  Helper::log(
    "Generating gamefield with size: "
    + to_string(sizeX)
    + " x "
    + to_string(sizeY) 
    + " and fill: " 
    + to_string(fill) 
    + "%"
  );

  if (gamefield) gamefield->deleteGamefield();

  gamefield = new Gamefield(sizeX, sizeY);
  gamefield->setGameContainer(this);

  this->setState(GAME_GENERATING);
  QtConcurrent::run(gamefield, &Gamefield::populateGamefield, fill, GENERATION_CURRENT); //could take a while, set status and catch UI events inside
}