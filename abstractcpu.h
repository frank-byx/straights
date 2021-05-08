#ifndef ABSTRACTCPU_H
#define ABSTRACTCPU_H

#include "game.h"

class AbstractCPU {
  Game *game;
  int player;
public:
  AbstractCPU(Game *game, int player);
  virtual void play() = 0;
  int getPlayer() const;
  Game *getGame() const;
};

#endif
