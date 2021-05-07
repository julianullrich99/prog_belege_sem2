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

void Helper::log(QString data) {
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