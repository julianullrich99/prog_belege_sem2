#include "fileservice.h"

Fileservice::Fileservice(Game *gameContainer) {
  this->gameContainer = gameContainer;
}

QString Fileservice::openFileSelector() {
  return QFileDialog::getOpenFileName(
    nullptr,
    QString("Choose file to open"),
    QString("templates")
  );
}

QString Fileservice::saveFileSelector() {
  return QFileDialog::getSaveFileName(
    nullptr,
    QString("Choose file to save to"),
    QString("templates/template.txt")
  );
}

bool Fileservice::writeGenerationToFile(QString filename) {
  QFile file(filename);

  if (!file.open(QIODevice::WriteOnly)) return false;

  QTextStream out(&file);
  out << fileSignature << "\n";

  const int gameHeight = gameContainer->getGamefield()->getSizeY();
  for (int i = 0; i < gameHeight; i++) {
    out << gameContainer->getGamefield()->convertRowToStringForFile(i, GENERATION_CURRENT) << "\n";
  }
  Helper::log("File saved successfully");
  return true;
}

bool Fileservice::fileExistsValid(QString filename) {
  if (!QFile::exists(filename)) return false;

  QFile file(filename);
  if (!file.open(QIODevice::ReadOnly)) return false;

  QByteArray firstLine = file.readLine();

  return firstLine.left(firstLine.length() - 1).compare(fileSignature) == 0;
}

bool Fileservice::readFileToGeneration(QString filename) {
  if (!QFile::exists(filename)) return false;

  QFile file(filename);
  if (!file.open(QIODevice::ReadOnly)) return false;

  QByteArray firstLine = file.readLine(); //skipping first line

  if (!this->getDimensionsFromFile(filename)) return false;

  Helper::log("Generating field " + to_string(fileWidth) + " x " + to_string(fileHeight));
  Gamefield *gamefield = gameContainer->generateEmptyGamefield(fileWidth, fileHeight);

  for (int i = 0; i < fileHeight; i++) {
    QByteArray line = file.readLine();
    line = line.left(line.length() - 1); // cut away newline character

    const char* lineData = line.data();

    for (int j = 0; j < line.length(); j++) {
      gamefield->setCellState(j, i, (lineData[j] == '1') ? CELL_ALIVE : CELL_DEAD, GENERATION_CURRENT);
    }
  }

  return true;
}

bool Fileservice::getDimensionsFromFile(QString filename) {
  if (!QFile::exists(filename)) return false;

  QFile file(filename);
  if (!file.open(QIODevice::ReadOnly)) return false;

  QByteArray firstLine = file.readLine(); //skipping first line

  int linecount = 0;
  int width = 0;
  while (!file.atEnd()) {
    linecount++;

    QByteArray line = file.readLine();
    if (!width) width = line.length() - 1;
  }

  this->fileWidth = width;
  this->fileHeight = linecount;

  return true;
}
