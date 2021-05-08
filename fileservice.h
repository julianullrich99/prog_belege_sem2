#ifndef FILESERVICE_H
#define FILESERVICE_H

#include <stdlib.h>
#include <string>
#include <QFile>
#include <QFileDialog>
#include "helper.h"
#include "cellstate.h"
#include "gamestate.h"
#include "game.h"

class Game;

using namespace std;

class Fileservice {
  public:
    Fileservice(Game *gameContainer);
    bool fileExistsValid(QString filename);
    bool readFileToGeneration(QString filename);
    bool writeGenerationToFile(QString filename);
    bool getDimensionsFromFile(QString filename);
    QString openFileSelector();
    QString saveFileSelector();

  private:
    Game *gameContainer;

    const char *fileSignature = "orangensaft";

    int fileWidth;
    int fileHeight;

};



#endif