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
  fieldwindow = nullptr;
}

Window* Game::getWindow() {
  return this->controlWindow;
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
  if (currentState != GAME_IDLE) return;

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

  QFuture<void> fieldReady = QtConcurrent::run(gamefield, &Gamefield::populateGamefield, fill, GENERATION_CURRENT); //could take a while, set status and catch UI events inside
  fieldReady.waitForFinished();

  this->showFieldwindow();
}

void Game::stepNextGeneration() {
  this->gamefield->generateNextGeneration();
  this->gamefield->applyNextGeneration();
  this->gamefield->printGamefieldToConsole(GENERATION_CURRENT);
  this->fieldwindow->reRender();
}

void Game::showFieldwindow() {
  Helper::log("Showing gamefield window");

  if (currentState == GAME_IDLE || (this->fieldwindow && this->fieldwindow->isVisible())) return;

  this->fieldwindow = new Fieldwindow(this->gamefield);
  this->fieldwindow->show();
  this->fieldwindow->setFocus();
}

void Game::clearFieldwindow() {
  this->fieldwindow = NULL;
}