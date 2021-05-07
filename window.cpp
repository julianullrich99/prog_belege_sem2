#include "window.h"
#include "helper.h"

#include <stdlib.h>
#include <iostream>

#include <QtWidgets>

Window::Window() {
    QGridLayout *mainLayout = new QGridLayout;

    QLabel* titleLabel = new QLabel("Spiel des Lebens");
    mainLayout->addWidget(titleLabel, 0, 0);

    statusLabel = new QLabel("");
    mainLayout->addWidget(statusLabel, 0, 2);

    generateGamefieldButton = new QPushButton("generate");
    randomizeGamefieldButton = new QPushButton("randomize");
    closeGamefieldButton = new QPushButton("close gamefield");
    startSimulationButton = new QPushButton("start simulation");
    pauseSimulationButton = new QPushButton("pause simulation");
    stepNextGenerationButton = new QPushButton("step simulation");

    mainLayout->addWidget(generateGamefieldButton, 1, 2);
    mainLayout->addWidget(randomizeGamefieldButton, 2, 2);
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

    connect(generateGamefieldButton, &QPushButton::clicked, this, &Window::generateGameFieldEvent);
    connect(gamefieldFillPercentageSlider, &QSlider::valueChanged, this, &Window::sliderChangedHandler);

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
    gamefieldFillPercentageSlider->value()
  );

};

void Window::sliderChangedHandler() {
  int value = gamefieldFillPercentageSlider->value();
  QString stringVal = QString::fromStdString("Fill: " + to_string(value) + "%");
  gamefieldFillPercentageLabel->setText(stringVal);
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
  }

  statusLabel->setText(QString::fromStdString(stateString));
};

void Window::setGameContainer(Game *game) {
  gameContainer = game;
}

Game* Window::getGameContainer() {
  return gameContainer;
}