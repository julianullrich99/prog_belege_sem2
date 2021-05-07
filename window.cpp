#include "window.h"
#include "helper.h"

#include <stdlib.h>
#include <iostream>

#include <QtWidgets>

Window::Window() {
    QGridLayout *mainLayout = new QGridLayout;

    generateGamefieldButton = new QPushButton("generate");
    randomizeGamefieldButton = new QPushButton("randomize");
    closeGamefieldButton = new QPushButton("close gamefield");
    startSimulationButton = new QPushButton("start simulation");
    pauseSimulationButton = new QPushButton("pause simulation");
    stepNextGenerationButton = new QPushButton("step simulation");

    mainLayout->addWidget(generateGamefieldButton);
    mainLayout->addWidget(randomizeGamefieldButton);
    mainLayout->addWidget(closeGamefieldButton);
    mainLayout->addWidget(startSimulationButton);
    mainLayout->addWidget(pauseSimulationButton);
    mainLayout->addWidget(stepNextGenerationButton);

    gamefieldSizeXLabel = new QLabel("sizeX");
    gamefieldSizeYLabel = new QLabel("sizeY");
    gamefieldSizeXInput = new QLineEdit("20");
    gamefieldSizeYInput = new QLineEdit("20");
    mainLayout->addWidget(gamefieldSizeXLabel);
    mainLayout->addWidget(gamefieldSizeXInput);
    mainLayout->addWidget(gamefieldSizeYLabel);
    mainLayout->addWidget(gamefieldSizeYInput);

    gamefieldFillPercentageLabel = new QLabel("50%");
    gamefieldFillPercentageSlider = new QSlider(Qt::Horizontal);
    gamefieldFillPercentageSlider->setMaximum(100);
    gamefieldFillPercentageSlider->setMinimum(0);
    gamefieldFillPercentageSlider->setSliderPosition(50);
    mainLayout->addWidget(gamefieldFillPercentageLabel);
    mainLayout->addWidget(gamefieldFillPercentageSlider);

    connect(generateGamefieldButton, &QPushButton::clicked, this, &Window::generateGameFieldEvent);
    connect(gamefieldFillPercentageSlider, &QSlider::valueChanged, this, &Window::sliderChangedHandler);

    setLayout(mainLayout);

    setWindowTitle("Spiel des Lebens oder so");

};


void Window::userEvent() {
  Helper::log("userEvent triggered");
};

void Window::generateGameFieldEvent() {
  Helper::log("Generating gamefield with size:");
  Helper::log(Window::gamefieldSizeXInput->text());
  Helper::log(Window::gamefieldSizeYInput->text());
};

void Window::sliderChangedHandler() {
  int value = gamefieldFillPercentageSlider->value();
  QString stringVal = QString::fromStdString(to_string(value) + "%");
  gamefieldFillPercentageLabel->setText(stringVal);
}

void Window::gameStateChangedEvent() {

};