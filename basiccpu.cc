#include "basiccpu.h"
#include "exception.h"
#include <vector>

BasicCPU::BasicCPU(Game *game, int player) : AbstractCPU{game, player} {}

void BasicCPU::play() {
  if (getPlayer() != getGame()->getCurrentPlayer()) {
    throw InvalidMoveException{};
  }
  std::vector<Card> legalMoves = getGame()->getLegalMoves();
  std::vector<Card> hand = getGame()->getCurrentPlayerHand();
  if (legalMoves.empty()) {
    getGame()->discard(hand.front());
  } else {
    getGame()->play(legalMoves.front());
  }
}

