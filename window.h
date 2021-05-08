#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include "gamestate.h"
#include "game.h"
#include "helper.h"
#include <stdlib.h>
#include <iostream>

#include <QtWidgets>

class QLabel;
class QPushButton;
class QLineEdit;
class QSlider;
class Game;

class Window : public QWidget {
  Q_OBJECT

public:
  Window();
  virtual ~Window(){};
  void changeGameStateDisplay(gameState);
  void setGameContainer(Game *);
  Game *getGameContainer();
  void setInputLabelsAfterFileLoad(int height, int width, int fill);
  void closeEvent(QCloseEvent *);

private slots:
  void userEvent();
  void generateGameFieldEvent();
  void sliderChangedHandler();
  void stepNextGenerationEvent();
  void showGamefieldEvent();
  void simulationSpeedChangedHandler();
  void startSimulationEvent();
  void pauseSimulationEvent();
  void closeGamefieldEvent();
  void editGamefieldTriggerEvent();
  void loadFileEvent();
  void saveFileEvent();

public slots:
  void handleTimerEvent();

private:
  Game *gameContainer;

  QLabel *statusLabel;

  QPushButton *generateGamefieldButton;
  QPushButton *closeGamefieldButton;
  QPushButton *startSimulationButton;
  QPushButton *pauseSimulationButton;
  QPushButton *stepNextGenerationButton;
  QPushButton *editGamefieldButton;

  QLabel *gamefieldSizeXLabel;
  QLabel *gamefieldSizeYLabel;
  QLineEdit *gamefieldSizeXInput;
  QLineEdit *gamefieldSizeYInput;

  QLabel *gamefieldFillPercentageLabel;
  QSlider *gamefieldFillPercentageSlider;

  QLabel *simulationSpeedLabel;
  QSlider *simulationSpeedSlider;

  QPushButton *loadFileButton;
  QPushButton *saveFileButton;

  void enableGamefieldControls(gameState);

  bool editGameFieldEnabled;
};

#endif
