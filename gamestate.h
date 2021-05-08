
#ifndef GAMESTATE_H
#define GAMESTATE_H

enum gameState {
  GAME_IDLE, // in menu, doing nothing
  GAME_RUNNING, // running simulation
  GAME_STOPPED, // simulation stopped (via user or automatically)
  GAME_PREPARED, // startState loaded, ready to start
  GAME_GENERATING
};

#endif