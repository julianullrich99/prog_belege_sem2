#include <stdlib.h>
#include <string>
using namespace std;

enum cellState {
  CELL_ALIVE,
  CELL_DEAD
};

class Gamefield {
  public:
    Gamefield(int, int);
    cellState getCellState(int, int);
    void setCellState(int, int, cellState);
    void generateNextGeneration();
    void applyNextGeneration();
    int getCurrentGenerationNumber();

  private:
    cellState* currentGeneration = nullptr;
    cellState* nextGeneration = nullptr;
    int currentGenerationNumber;
    int sizeX;
    int sizeY;
    void setGamefieldSize(int, int);

};