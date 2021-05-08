#ifndef FIELDWINDOW_H
#define FIELDWINDOW_H

#include <stdlib.h>
#include <string>
#include <QtWidgets>
#include <QCloseEvent>
using namespace std;

#include "gamefield.h"
#include "gamestate.h"
#include "game.h"
#include "renderarea.h"

#include "window.h"

class Gamefield;
class QLabel;
class QPixmap;
class Renderarea;

class Fieldwindow : public QWidget {
  Q_OBJECT

  public:
    Fieldwindow(Gamefield *);
    virtual ~Fieldwindow(){};
    Gamefield *getGamefieldContainer();
    void reRender();

  private slots:

  private:
    Gamefield *gamefieldContainer;
    void closeEvent(QCloseEvent *);

    QLabel *telemetryLabel;
    Renderarea *renderarea;

};


#endif