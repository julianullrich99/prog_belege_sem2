#include "fieldwindow.h"

#include <stdlib.h>
#include <string>
#include <iostream>

using namespace std;

Fieldwindow::Fieldwindow(Gamefield *gamefieldContainer) {
  this->gamefieldContainer = gamefieldContainer;

  setAttribute(Qt::WA_DeleteOnClose);

  QVBoxLayout *mainLayout = new QVBoxLayout(this);

  telemetryLabel = new QLabel(QString::fromStdString(this->getTelemetryString()));
  mainLayout->addWidget(telemetryLabel);

  renderarea = new Renderarea(this, this);
  mainLayout->addWidget(renderarea);

  setLayout(mainLayout);

  setWindowTitle("Spiel des Lebens oder so");
}

void Fieldwindow::closeEvent(QCloseEvent *event) {
  Helper::log("Closed");
  this->gamefieldContainer->getGameContainer()->setState(GAME_IDLE);
  this->gamefieldContainer->getGameContainer()->clearFieldwindow();
}

Gamefield* Fieldwindow::getGamefieldContainer() {
  return this->gamefieldContainer;
}

string Fieldwindow::getTelemetryString() {
  return "Generation: " +
  to_string(this->gamefieldContainer->getCurrentGenerationNumber()) +
  ", Lebend: " +
  to_string(this->gamefieldContainer->getCurrentlyAliveCells(GENERATION_CURRENT));
}

void Fieldwindow::reRender() {
  telemetryLabel->setText(QString::fromStdString(this->getTelemetryString()));
  repaint();
}