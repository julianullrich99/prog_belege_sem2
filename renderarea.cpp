#include "renderarea.h"

using namespace std;

Renderarea::Renderarea(QWidget *parent, Fieldwindow *fieldwindow) {
  this->fieldwindow = fieldwindow;
  this->sizeX = this->fieldwindow->getGamefieldContainer()->getSizeX();
  this->sizeY = this->fieldwindow->getGamefieldContainer()->getSizeY();

  this->editingEnabled = false;

  setFixedSize(sizeX * 10, sizeY * 10);
}

void Renderarea::paintEvent(QPaintEvent *event) {
  QPainter painter(this);

  for (int i = 0; i < sizeX; i++) {
    for (int j = 0; j < sizeY; j++) {
      QColor cellColor(0,255,0);
      if (this->fieldwindow->getGamefieldContainer()->getCellState(i, j, GENERATION_CURRENT) == CELL_DEAD)
        cellColor.setRgb(255,0,0);
      painter.fillRect(i * 10, j * 10, 10, 10, cellColor);

      if (Helper::isDebugEnabled())
        painter.drawText(i * 10, (j + 1) * 10, QString::fromStdString( // debug neigbour rendering
          to_string(this->fieldwindow->getGamefieldContainer()->getCellNeighbours(i, j))
        ));
    }
  }

  if (this->editingEnabled) {
    painter.drawLine(0, 0, this->width(), 0);
    painter.drawLine(0, 0, 0, this->height());
    for (int i = 0; i < sizeX; i++) {
      for (int j = 0; j < sizeY; j++) {
        painter.drawLine((i + 1) * 10 - 1, 0, (i + 1) * 10 - 1, this->height());
        painter.drawLine(0, (j + 1) * 10 - 1, this->width(), (j + 1) * 10 - 1);
      }
    }
  }

}

void Renderarea::mousePressEvent(QMouseEvent *event) {
  Helper::debug("mouseEvent at " + to_string(event->x()) + " " + to_string(event->y()));
  if (!editingEnabled) return;

  fieldwindow->handleFlipCell(event->x(), event->y());
}

void Renderarea::showEditGrid(bool arg) {
  this->editingEnabled = arg;
  this->repaint();
}