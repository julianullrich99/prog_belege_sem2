#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>

#include "cellstate.h"
#include "fieldwindow.h"

class Fieldwindow;

class Renderarea : public QWidget {
  Q_OBJECT

  public:
    Renderarea(QWidget *parent, Fieldwindow *);
    ~Renderarea() {};
    void paintEvent(QPaintEvent *event);

  private:
    Fieldwindow *fieldwindow;
    int sizeX;
    int sizeY;
};

#endif
