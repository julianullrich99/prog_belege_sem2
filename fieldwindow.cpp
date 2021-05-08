#include "fieldwindow.h"

#include <stdlib.h>
#include <string>
#include <iostream>

using namespace std;

Fieldwindow::Fieldwindow(Gamefield *gamefieldContainer) {
  this->gamefieldContainer = gamefieldContainer;

  setAttribute(Qt::WA_DeleteOnClose);

  mainLayout = new QVBoxLayout(this);

  telemetryLabel = new QLabel(QString::fromStdString(this->getTelemetryString()));
  mainLayout->addWidget(telemetryLabel);

  renderarea = new Renderarea(this, this);
  mainLayout->addWidget(renderarea);

  editHintLabel = new QLabel(QString(""));
  mainLayout->addWidget(editHintLabel);

  setLayout(mainLayout);

  setWindowTitle("Game of Life - Gamefield");
}

void Fieldwindow::closeEvent(QCloseEvent *event) {
  Helper::log("Closed Fieldwindow");
  this->gamefieldContainer->getGameContainer()->pauseSimulation();
  this->gamefieldContainer->getGameContainer()->clearFieldwindow();
  this->gamefieldContainer->getGameContainer()->setState(GAME_IDLE);
}

Gamefield* Fieldwindow::getGamefieldContainer() {
  return this->gamefieldContainer;
}

string Fieldwindow::getTelemetryString() {
  return "Generation: " +
  to_string(this->gamefieldContainer->getCurrentGenerationNumber()) +
  ", Alive: " +
  to_string(this->gamefieldContainer->getCurrentlyAliveCells(GENERATION_CURRENT));
}

void Fieldwindow::reRender() {
  telemetryLabel->setText(QString::fromStdString(this->getTelemetryString()));
  repaint();
}

void Fieldwindow::showEditHintLabel(bool arg) {
  if (arg)
    editHintLabel->setText(QString("edit by clicking field"));
  else {
    editHintLabel->setText(QString(""));
  }
}

void Fieldwindow::enableEditGamefield(bool arg) {
  this->showEditHintLabel(arg);
  renderarea->showEditGrid(arg);
}

void Fieldwindow::handleFlipCell(int x, int y) {
  cellState currentCellState = gamefieldContainer->getCellState(x / 10, y / 10, GENERATION_CURRENT);
  cellState newCellState = (currentCellState == CELL_ALIVE) ? CELL_DEAD : CELL_ALIVE;
  gamefieldContainer->setCellState(x / 10, y / 10, newCellState, GENERATION_CURRENT);
  renderarea->repaint();
}