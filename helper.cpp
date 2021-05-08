#include "helper.h"

#include <stdlib.h>
#include <string>
#include <iostream>

using namespace std;

void Helper::logString(string data){
  if (Helper::isLoggingEnabled())
  std::cout << data << std::endl;
}

Helper* Helper::getInstance() {
  if (!instance)
  instance = new Helper;
  return instance;
}

void Helper::log(string data) {
  Helper::logString(data);
};

void Helper::log(char* data) {
  Helper::logString(data);
};

void Helper::log(const char* data) {
  Helper::logString(data);
};

void Helper::log(QString data) {
  Helper::logString(Helper::toString(data));
}

void Helper::debug(string data) {
  if (Helper::isDebugEnabled())
  Helper::logString(data);
};

void Helper::debug(char* data) {
  if (Helper::isDebugEnabled())
  Helper::logString(data);
};

void Helper::debug(const char* data) {
  if (Helper::isDebugEnabled())
  Helper::logString(data);
};

void Helper::debug(QString data) {
  if (Helper::isDebugEnabled())
  Helper::logString(Helper::toString(data));
}

string Helper::toString(QString str) {
  return str.toStdString();
}

void Helper::enableLogging(bool arg) {
  Helper::getInstance()->loggingEnabled = arg;
}

bool Helper::isLoggingEnabled() {
  return Helper::getInstance()->loggingEnabled;
}

void Helper::enableDebug(bool arg) {
  Helper::getInstance()->debugEnabled = arg;
}

bool Helper::isDebugEnabled() {
  return Helper::getInstance()->debugEnabled;
}

string Helper::formatCellOutput(cellState state) {
  switch (state) {
    case CELL_ALIVE:
      return "1";
      break;
    case CELL_DEAD:
      return "0";
      break;
    case CELL_ERROR:
      return "E";
      break;
  }
}

void Helper::errorDialog(string message) {
  QErrorMessage *error = new QErrorMessage();
  error->showMessage(QString::fromStdString(message));
}

void Helper::message(string message) {
  QMessageBox *msgBox = new QMessageBox();
  msgBox->setText(QString::fromStdString(message));
  msgBox->exec();
}