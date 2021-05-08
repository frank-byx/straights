#ifndef TABLE_H
#define TABLE_H

#include "card.h"
#include <vector>

class Table {
  std::vector<std::vector<Card>> piles;   // one pile for each suit in order of Suit enumeration values
public:
  Table();
  void push_front(Card card);             // adds card to the front of the pile for card's suit
  void push_back(Card card);              // adds card to the back of the pile for card's suit
  void clear();
  std::vector<Card> getPile(Suit suit) const;
};

#endif
