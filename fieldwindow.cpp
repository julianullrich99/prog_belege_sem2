#include "fieldwindow.h"

#include <stdlib.h>
#include <string>
#include <iostream>

using namespace std;

Fieldwindow::Fieldwindow(Gamefield *gamefieldContainer) {
  this->gamefieldContainer = gamefieldContainer;

  setAttribute(Qt::WA_DeleteOnClose);

  QVBoxLayout *mainLayout = new QVBoxLayout(this);

  telemetryLabel = new QLabel("Generation 0, 42 Lebend");
  mainLayout->addWidget(telemetryLabel);

  renderarea = new Renderarea(this, this);
  mainLayout->addWidget(renderarea);

  setLayout(mainLayout);

  setWindowTitle("Spiel des Lebens oder so");
}

void Fieldwindow::closeEvent(QCloseEvent *event) {
  Helper::log("Closed");
  this->gamefieldContainer->getGameContainer()->setState(GAME_PREPARED);
  this->gamefieldContainer->getGameContainer()->clearFieldwindow();
}

Gamefield* Fieldwindow::getGamefieldContainer() {
  return this->gamefieldContainer;
}

void Fieldwindow::reRender() {
  repaint();
}