#ifndef CARD_H
#define CARD_H

#include<utility>

extern const int RANKS;

enum Rank { Ace, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King };

extern const int SUITS;

enum Suit { Clubs, Diamonds, Hearts, Spades };

class Card {
  std::pair<Rank,Suit> signature;
public:
  Card(); // default constructor is only used for initializing a state object
  Card(Rank rank, Suit suit);
  Rank getRank() const;
  Suit getSuit() const;
  bool comesBefore(const Card &other) const; // check if this card is left-adjacent to the other card
  bool comesAfter(const Card &other) const; // check if this card is right-adjacent to the other card
  bool operator==(const Card &other) const;
};

#endif
