#include "game.h"
#include "helper.h"
// #include "window.h"

#include <stdlib.h>
#include <string>
#include <iostream>

#include <QObject>

using namespace std;

Game::Game() {
  currentState = GAME_IDLE;
  controlWindow = new Window();
  controlWindow->setGameContainer(this);

  gamefield = nullptr;
  fieldwindow = nullptr;
  simulationTimer = nullptr;
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

  this->setState(GAME_PREPARED);

  this->showFieldwindow();
}

void Game::stepNextGeneration() {
  this->gamefield->generateNextGeneration();
  this->gamefield->applyNextGeneration();
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

void Game::handleTimerEvent() {
  this->stepNextGeneration();
}

void Game::setSimulationSpeed(int time) {
  this->simulationSpeed = time;
  if (this->simulationTimer) {
    if (currentState == GAME_RUNNING) // only need to stop if already running
      simulationTimer->stop();
  } else {
    simulationTimer = new QTimer();
    QObject::connect(simulationTimer, &QTimer::timeout, controlWindow, &Window::handleTimerEvent);
  }
  if (currentState == GAME_RUNNING)
    simulationTimer->start(this->simulationSpeed);
}

void Game::startSimulation() {
  this->setState(GAME_RUNNING);
  this->setSimulationSpeed(this->simulationSpeed);
}

void Game::pauseSimulation() {
  this->setState(GAME_STOPPED);
  this->simulationTimer->stop();
}

Fieldwindow* Game::getFieldwindow() {
  return this->fieldwindow;
}

gameState Game::getCurrentState() {
  return currentState;
}

void Game::enableEditGamefield(bool arg) {
  if (arg) this->setState(GAME_EDITING);
  else this->setState(GAME_PREPARED);
  fieldwindow->enableEditGamefield(arg);
}