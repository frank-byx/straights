#include "card.h"

extern const int RANKS = 13;

extern const int SUITS = 4;

Card::Card() : signature{Ace, Clubs} {}

Card::Card(Rank rank, Suit suit) : signature{rank, suit} {}

Rank Card::getRank() const {
  return std::get<0>(signature);
}

Suit Card::getSuit() const {
  return std::get<1>(signature);
}

bool Card::comesBefore(const Card &other) const {
  return getSuit() == other.getSuit() && getRank() == other.getRank() - 1;
}

bool Card::comesAfter(const Card &other) const {
  return getSuit() == other.getSuit() && getRank() == other.getRank() + 1;
}

bool Card::operator==(const Card &other) const {
  return signature == other.signature;
}
