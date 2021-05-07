#include "gamefield.h"
#include "helper.h"

#include <stdlib.h>
#include <string>
#include <iostream>

using namespace std;

Gamefield::Gamefield(int sizeX, int sizeY) {
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