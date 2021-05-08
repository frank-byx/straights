#ifndef PLAYER_H
#define PLAYER_H

#include "card.h"
#include <vector>

class Player {
  std::vector<Card> hand;
  std::vector<Card> discarded;
public:
  std::vector<Card> getHand() const;
  std::vector<Card> getDiscarded() const;
  void addToHand(Card card);
  void addToDiscarded(Card card);
  void removeFromHand(Card card);
  void clear();
};

#endif
