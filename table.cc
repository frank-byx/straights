#include "table.h"

Table::Table() : piles(SUITS) {}

void Table::push_front(Card card) {
  std::vector<Card> &pile = piles.at(card.getSuit());
  pile.insert(pile.begin(), card);
}

void Table::push_back(Card card) {
  std::vector<Card> &pile = piles.at(card.getSuit());
  pile.push_back(card);
}

void Table::clear() {
  for (std::vector<Card> &pile : piles) {
    pile.clear();
  }
}

std::vector<Card> Table::getPile(Suit suit) const {
  return piles.at(suit);
}

