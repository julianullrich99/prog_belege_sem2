#ifndef HELPER_H
#define HELPER_H

#include <stdlib.h>
#include <string>
#include <QWidget>
#include <QErrorMessage>
#include <QMessageBox>
#include "cellstate.h"

using namespace std;

class QString;

class Helper {
  public:
    static void enableLogging(bool);
    static bool isLoggingEnabled();

    static void enableDebug(bool);
    static bool isDebugEnabled();

    static void log(string);
    static void log(QString);
    static void log(char*);
    static void log(const char*);
    static void debug(string);
    static void debug(QString);
    static void debug(char*);
    static void debug(const char*);
    static string toString(QString);

    static void errorDialog(string);
    static void message(string);

    static string formatCellOutput(cellState);


  private:
    bool loggingEnabled = false;
    bool debugEnabled = false;
    static void logString(string);
    static Helper *getInstance();
    static Helper *instance;
    Helper(){};
};

#endif