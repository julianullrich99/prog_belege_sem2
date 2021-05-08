#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <stdlib.h>
#include <string>
#include <QWidget>
#include "helper.h"
#include "cellstate.h"
#include "gamestate.h"
#include "game.h"

class Game;

using namespace std;

class Gamefield {
  public:
    Gamefield(int sizeX, int sizeY);
    cellState getCellState(int x, int y, generation);
    void setCellState(int x, int y, cellState, generation);
    void generateNextGeneration();
    void applyNextGeneration();
    int getCurrentGenerationNumber();
    void deleteGamefield();
    void populateGamefield(int fill, generation);
    void printGamefieldToConsole(generation);
    void cleanGamefield(cellState targetState, generation targetGeneration);
    void setGameContainer(Game *);
    Game* getGameContainer();
    int getSizeX();
    int getSizeY();
    int getCellNeighbours(int x, int y);
    int getCurrentlyAliveCells(generation);
    QString convertRowToStringForFile(int row, generation);

  private:
    cellState* currentGeneration = nullptr;
    cellState* nextGeneration = nullptr;
    Game *gameContainer;
    int currentGenerationNumber;
    int sizeX;
    int sizeY;
    void setGamefieldSize(int sizeX, int sizeY);
    int getOffsetForCords(int x, int y);
    cellState getCellStateByOffset(int offset, generation target);
    void setCellStateByOffset(int offset, cellState state, generation target);
    cellState executeRulesOnCell(cellState beforeState, int neighbours);

};

#endif