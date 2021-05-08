#ifndef BASICCPU_H
#define BASICCPU_H

#include "game.h"
#include "abstractcpu.h"

class BasicCPU : public AbstractCPU {
public:
  BasicCPU(Game *game, int player);
  virtual void play() override;
};

#endif
