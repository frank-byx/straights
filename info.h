#ifndef INFO_H
#define INFO_H

#include "card.h"
#include <vector>

// Info contains all information about the current snapshot of the game state that is relevant to the observer.
// Note that this snapshot is from the perspective of the current player.

struct Info {
  int currentPlayer;
  std::vector<Card> clubsPile;
  std::vector<Card> diamondsPile;
  std::vector<Card> heartsPile;
  std::vector<Card> spadesPile;
  std::vector<Card> playerHand;
  std::vector<Card> legalMoves;
};

#endif
