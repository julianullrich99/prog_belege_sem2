#include "window.h"
#include "helper.h"

#include <stdlib.h>
#include <iostream>

#include <QtWidgets>

Window::Window() {
  gameContainer = 0;
  editGameFieldEnabled = false;

  QGridLayout *mainLayout = new QGridLayout;

  QLabel *titleLabel = new QLabel("Spiel des Lebens");
  mainLayout->addWidget(titleLabel, 0, 0);

  statusLabel = new QLabel("");
  mainLayout->addWidget(statusLabel, 0, 2);

  generateGamefieldButton = new QPushButton("generate random");
  closeGamefieldButton = new QPushButton("close gamefield");
  startSimulationButton = new QPushButton("start simulation");
  pauseSimulationButton = new QPushButton("pause simulation");
  stepNextGenerationButton = new QPushButton("step simulation");
  editGamefieldButton = new QPushButton("enable editing");

  mainLayout->addWidget(generateGamefieldButton, 1, 2);
  mainLayout->addWidget(editGamefieldButton, 2, 2);
  mainLayout->addWidget(closeGamefieldButton, 3, 2);
  mainLayout->addWidget(startSimulationButton, 4, 2);
  mainLayout->addWidget(pauseSimulationButton, 5, 2);
  mainLayout->addWidget(stepNextGenerationButton, 6, 2);

  gamefieldSizeXLabel = new QLabel("sizeX");
  gamefieldSizeYLabel = new QLabel("sizeY");
  gamefieldSizeXInput = new QLineEdit("20");
  gamefieldSizeYInput = new QLineEdit("20");
  mainLayout->addWidget(gamefieldSizeXLabel, 1, 0);
  mainLayout->addWidget(gamefieldSizeXInput, 1, 1);
  mainLayout->addWidget(gamefieldSizeYLabel, 2, 0);
  mainLayout->addWidget(gamefieldSizeYInput, 2, 1);

  gamefieldFillPercentageLabel = new QLabel("50%");
  gamefieldFillPercentageSlider = new QSlider(Qt::Horizontal);
  gamefieldFillPercentageSlider->setMaximum(100);
  gamefieldFillPercentageSlider->setMinimum(0);
  gamefieldFillPercentageSlider->setSliderPosition(50);
  mainLayout->addWidget(gamefieldFillPercentageLabel, 3, 0);
  mainLayout->addWidget(gamefieldFillPercentageSlider, 3, 1);

  simulationSpeedLabel = new QLabel("Speed: 100ms");
  simulationSpeedSlider = new QSlider(Qt::Horizontal);
  simulationSpeedSlider->setMaximum(1000);
  simulationSpeedSlider->setMinimum(10);
  simulationSpeedSlider->setSliderPosition(100);
  mainLayout->addWidget(simulationSpeedLabel, 4, 0);
  mainLayout->addWidget(simulationSpeedSlider, 4, 1);

  connect(generateGamefieldButton, &QPushButton::clicked, this, &Window::generateGameFieldEvent);
  connect(stepNextGenerationButton, &QPushButton::clicked, this, &Window::stepNextGenerationEvent);
  connect(gamefieldFillPercentageSlider, &QSlider::valueChanged, this, &Window::sliderChangedHandler);
  connect(simulationSpeedSlider, &QSlider::valueChanged, this, &Window::simulationSpeedChangedHandler);
  connect(startSimulationButton, &QPushButton::clicked, this, &Window::startSimulationEvent);
  connect(pauseSimulationButton, &QPushButton::clicked, this, &Window::pauseSimulationEvent);
  connect(closeGamefieldButton, &QPushButton::clicked, this, &Window::closeGamefieldEvent);
  connect(editGamefieldButton, &QPushButton::clicked, this, &Window::editGamefieldTriggerEvent);

  setLayout(mainLayout);

  setWindowTitle("Spiel des Lebens oder so");
};

void Window::userEvent() {
  Helper::log("userEvent triggered");
};

void Window::generateGameFieldEvent() {
  gameContainer->generateGameField(
      stoi(Helper::toString(gamefieldSizeXInput->text())),
      stoi(Helper::toString(gamefieldSizeYInput->text())),
      gamefieldFillPercentageSlider->value());
};

void Window::stepNextGenerationEvent() {
  Helper::log("Generating next generation");
  gameContainer->stepNextGeneration();
}

void Window::showGamefieldEvent() {
  Helper::log("Showing Gamefield");
  gameContainer->showFieldwindow();
}

void Window::startSimulationEvent() {
  Helper::log("Starting Simulation");
  gameContainer->startSimulation();
}

void Window::pauseSimulationEvent() {
  Helper::log("Pausing Simulation");
  gameContainer->pauseSimulation();
}

void Window::editGamefieldTriggerEvent() {
  Helper::log("Trigger Gamefield editing");
  if (gameContainer->getCurrentState() != GAME_PREPARED && gameContainer->getCurrentState() != GAME_EDITING) return;
  this->editGameFieldEnabled = !this->editGameFieldEnabled;
  editGamefieldButton->setText((this->editGameFieldEnabled) ? QString("disable editing") : QString("enable editing"));
  gameContainer->enableEditGamefield(this->editGameFieldEnabled);
}

void Window::handleTimerEvent() { // workaround for handling timer events (slots) because they need QObject
  gameContainer->handleTimerEvent();
}

void Window::sliderChangedHandler() {
  int value = gamefieldFillPercentageSlider->value();
  QString stringVal = QString::fromStdString("Fill: " + to_string(value) + "%");
  gamefieldFillPercentageLabel->setText(stringVal);
}

void Window::simulationSpeedChangedHandler() {
  int timeMs = simulationSpeedSlider->value();
  QString stringVal = QString::fromStdString("Speed: " + to_string(timeMs) + "ms");
  simulationSpeedLabel->setText(stringVal);
  gameContainer->setSimulationSpeed(timeMs);
}

void Window::closeGamefieldEvent() {
  gameContainer->getFieldwindow()->close();
}

void Window::enableGamefieldControls(gameState state) {
  switch (state) {
  case GAME_PREPARED:
    this->generateGamefieldButton->setEnabled(false);
    this->startSimulationButton->setEnabled(true);
    this->stepNextGenerationButton->setEnabled(true);
    this->closeGamefieldButton->setEnabled(true);
    this->pauseSimulationButton->setEnabled(false);
    this->gamefieldSizeXInput->setEnabled(false);
    this->gamefieldSizeYInput->setEnabled(false);
    this->gamefieldFillPercentageSlider->setEnabled(false);
    this->editGamefieldButton->setEnabled(true);
    break;
  case GAME_IDLE:
    this->generateGamefieldButton->setEnabled(true);
    this->startSimulationButton->setEnabled(false);
    this->stepNextGenerationButton->setEnabled(false);
    this->closeGamefieldButton->setEnabled(false);
    this->pauseSimulationButton->setEnabled(false);
    this->gamefieldSizeXInput->setEnabled(true);
    this->gamefieldSizeYInput->setEnabled(true);
    this->gamefieldFillPercentageSlider->setEnabled(true);
    this->editGamefieldButton->setEnabled(false);
    break;
  case GAME_RUNNING:
    this->generateGamefieldButton->setEnabled(false);
    this->startSimulationButton->setEnabled(false);
    this->stepNextGenerationButton->setEnabled(false);
    this->closeGamefieldButton->setEnabled(false);
    this->pauseSimulationButton->setEnabled(true);
    this->gamefieldSizeXInput->setEnabled(false);
    this->gamefieldSizeYInput->setEnabled(false);
    this->gamefieldFillPercentageSlider->setEnabled(false);
    this->editGamefieldButton->setEnabled(false);
    break;
  case GAME_STOPPED:
    this->generateGamefieldButton->setEnabled(false);
    this->startSimulationButton->setEnabled(true);
    this->stepNextGenerationButton->setEnabled(true);
    this->closeGamefieldButton->setEnabled(true);
    this->pauseSimulationButton->setEnabled(false);
    this->gamefieldSizeXInput->setEnabled(false);
    this->gamefieldSizeYInput->setEnabled(false);
    this->gamefieldFillPercentageSlider->setEnabled(false);
    this->editGamefieldButton->setEnabled(false);
    break;
  case GAME_EDITING:
    this->generateGamefieldButton->setEnabled(false);
    this->startSimulationButton->setEnabled(false);
    this->stepNextGenerationButton->setEnabled(false);
    this->closeGamefieldButton->setEnabled(false);
    this->pauseSimulationButton->setEnabled(false);
    this->gamefieldSizeXInput->setEnabled(false);
    this->gamefieldSizeYInput->setEnabled(false);
    this->gamefieldFillPercentageSlider->setEnabled(false);
    this->editGamefieldButton->setEnabled(true);
    break;
  default:
    return;
  }
}

void Window::changeGameStateDisplay(gameState newState) {
  string stateString = "";
  switch (newState) {
  case GAME_IDLE:
    stateString = "IDLE";
    break;
  case GAME_RUNNING:
    stateString = "RUNNING";
    break;
  case GAME_STOPPED:
    stateString = "STOPPED";
    break;
  case GAME_PREPARED:
    stateString = "PREPARED";
    break;
  case GAME_GENERATING:
    stateString = "GENERATING";
    break;
  case GAME_EDITING:
    stateString = "EDITING";
    break;
  }

  enableGamefieldControls(newState);

  statusLabel->setText(QString::fromStdString(stateString));
};

void Window::setGameContainer(Game *game) {
  gameContainer = game;
}

Game *Window::getGameContainer() {
  return gameContainer;
}