#include "gamefield.h"

using namespace std;

Gamefield::Gamefield(int sizeX, int sizeY) {
  gameContainer = 0;

  setGamefieldSize(sizeX, sizeY);
  currentGenerationNumber = 0;

  currentGeneration = new cellState[sizeX * sizeY];
  nextGeneration = new cellState[sizeX * sizeY];

  Helper::log("Generated empty Field for current and next Generation");
};

void Gamefield::setGamefieldSize(int sizeX, int sizeY) {
  Gamefield::sizeX = sizeX;
  Gamefield::sizeY = sizeY;
};

void Gamefield::cleanGamefield(cellState targetState = CELL_DEAD, generation targetGeneration = GENERATION_NEXT) {
  for (int i = 0; i < sizeX; i++)
    for (int j = 0; j < sizeY; j++)
      setCellState(i, j, targetState, targetGeneration);
};

void Gamefield::deleteGamefield() {
  delete[] currentGeneration;
  delete[] nextGeneration;
};

void Gamefield::populateGamefield(int fill, generation target = GENERATION_NEXT) {
  Helper::log("Populating gamefield");


  cleanGamefield(CELL_DEAD, GENERATION_CURRENT);

  srand(time(0));

  const int cellsToPopulate = sizeX * sizeY * fill / 100;
  int cellsCurrentlyPopulated = 0;

  Helper::debug("cells to populate:" + to_string(cellsToPopulate));

  const int maxOffset = getOffsetForCords(sizeX - 1, sizeY - 1);

  while (cellsCurrentlyPopulated < cellsToPopulate) {
    const int offset = rand() % maxOffset;
    Helper::debug("offset " + to_string(offset));

    cellState currentStatus = getCellStateByOffset(offset, target);
    Helper::debug("currentState" + Helper::formatCellOutput(currentStatus));

    if (currentStatus == CELL_DEAD) {
      setCellStateByOffset(offset, CELL_ALIVE, target);
      cellsCurrentlyPopulated++;
    }
  }

  Helper::log("Done generating field");
};

void Gamefield::printGamefieldToConsole(generation target = GENERATION_CURRENT) {
  for (int i = 0; i < sizeY; i++) {
    string line = "";
    for (int j = 0; j < sizeX; j++)
      line += Helper::formatCellOutput(getCellState(j, i, target));
    Helper::log(line);
  }
};

int Gamefield::getOffsetForCords(int x, int y) {
  if (y >= sizeY || x >= sizeX) return 0;

  return y * sizeX + x;
}

void Gamefield::applyNextGeneration() {
  cellState *temp = currentGeneration; // just swap so we dont have to realloc
  currentGeneration = nextGeneration;
  nextGeneration = temp;
  currentGenerationNumber++;
}

void Gamefield::setCellState(int x, int y, cellState state, generation targetGen = GENERATION_NEXT) {
  if (targetGen == GENERATION_CURRENT)
    *(currentGeneration + getOffsetForCords(x, y)) = state;
  else
    *(nextGeneration + getOffsetForCords(x, y)) = state;
}

cellState Gamefield::getCellState(int x, int y, generation target = GENERATION_CURRENT) {
  if (target == GENERATION_CURRENT)
    return *(currentGeneration + getOffsetForCords(x, y));
  else
    return *(nextGeneration + getOffsetForCords(x, y));
}

int Gamefield::getCurrentGenerationNumber() {
  return currentGenerationNumber;
}

cellState Gamefield::getCellStateByOffset(int offset, generation target = GENERATION_CURRENT) {
  if (offset > getOffsetForCords(sizeX - 1, sizeY - 1)) return CELL_ERROR;

  if (target == GENERATION_CURRENT)
    return *(currentGeneration + offset);
  else
    return *(nextGeneration + offset);
}

void Gamefield::setCellStateByOffset(int offset, cellState state, generation target = GENERATION_NEXT) {
  if (offset > getOffsetForCords(sizeX - 1, sizeY - 1)) return;

  if (target == GENERATION_CURRENT)
    *(currentGeneration + offset) = state;
  else
    *(nextGeneration + offset) = state;
}

void Gamefield::setGameContainer(Game *game) {
  gameContainer = game;
}

Game* Gamefield::getGameContainer() {
  return gameContainer;
}

int Gamefield::getSizeX() {
  return this->sizeX;
}

int Gamefield::getSizeY() {
  return this->sizeY;
}

void Gamefield::generateNextGeneration() {
  for (int i = 0; i < this->sizeX; i++)
    for (int j = 0; j < this->sizeY; j++) {
      cellState newState = this->executeRulesOnCell(
        this->getCellState(i, j, GENERATION_CURRENT),
        this->getCellNeighbours(i, j)
      );
      Helper::debug(string("afterState: ") + ((newState == CELL_ALIVE) ? "alive" : "dead"));
      this->setCellState(i, j, newState, GENERATION_NEXT);
    }
}

int Gamefield::getCellNeighbours(int x, int y) {

  cellState currVal = getCellState(x, y);
  int neighbours = 0;

  for (int k = x - 1; k <= x + 1; k++) {
    for (int l = y - 1; l <= y + 1; l++) {
      if ((k < 0 || k >= this->sizeX) ||
          (l < 0 || l >= this->sizeY) ||
          (k == x && l == y))
        continue;
      if (getCellState(k, l) == CELL_ALIVE) neighbours++;
    }
  }

  return neighbours;
}

cellState Gamefield::executeRulesOnCell(cellState beforeState, int neighbours) {
  Helper::debug(string("beforeState: ") + ((beforeState == CELL_ALIVE) ? "alive" : "dead") + " neighbours: " + to_string(neighbours));
  if (beforeState == CELL_ALIVE && (neighbours < 2 || neighbours > 3))
    return CELL_DEAD;
  else if (beforeState == CELL_DEAD && neighbours == 3)
    return CELL_ALIVE;

  return beforeState;

}

int Gamefield::getCurrentlyAliveCells(generation target = GENERATION_CURRENT) {
  int buf = 0;
  for (int i = 0; i < this->sizeX; i++)
    for (int j = 0; j < this->sizeY; j++)
      if (this->getCellState(i, j, target) == CELL_ALIVE) buf++;

  return buf;
}

QString Gamefield::convertRowToStringForFile(int row, generation target = GENERATION_CURRENT) {
  if (row >= sizeY) return "";

  string buf = "";
  for (int i = 0; i < sizeX; i++) {
    buf += Helper::formatCellOutput(getCellState(i, row, target));
  }

  return QString::fromStdString(buf);
}