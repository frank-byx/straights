#include "abstractcpu.h"

AbstractCPU::AbstractCPU(Game *game, int player) : game{game}, player{player} {}

int AbstractCPU::getPlayer() const {
  return player;
}

Game *AbstractCPU::getGame() const {
  return game;
}

