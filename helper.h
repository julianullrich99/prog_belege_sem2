#include <stdlib.h>
#include <string>
#include <QWidget>

using namespace std;

class QString;

class Helper {
  public:
    static void enableLogging(bool);
    static bool isLoggingEnabled();

    static void log(string);
    static void log(QString);
    static void log(char*);
    static string toString(QString);


  private:
    bool loggingEnabled = false;
    static void logString(string);
    static Helper *getInstance();
    static Helper *instance;
    Helper(){};
};