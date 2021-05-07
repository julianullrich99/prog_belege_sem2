#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <stdlib.h>
#include <string>
#include "helper.h"

using namespace std;

enum cellState {
  CELL_ALIVE,
  CELL_DEAD,
  CELL_ERROR
};

enum generation {
  GENERATION_CURRENT,
  GENERATION_NEXT
};

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

  private:
    cellState* currentGeneration = nullptr;
    cellState* nextGeneration = nullptr;
    int currentGenerationNumber;
    int sizeX;
    int sizeY;
    void setGamefieldSize(int sizeX, int sizeY);
    int getOffsetForCords(int x, int y);
    cellState getCellStateByOffset(int offset, generation target);
    void setCellStateByOffset(int offset, cellState state, generation target);

};

#endif