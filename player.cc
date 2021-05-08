#include "player.h"
#include <algorithm>

std::vector<Card> Player::getHand() const {
  return hand;
}

std::vector<Card> Player::getDiscarded() const {
  return discarded;
}

void Player::addToHand(Card card) {
  hand.push_back(card);
}

void Player::addToDiscarded(Card card) {
  discarded.push_back(card);
}

void Player::removeFromHand(Card card) {
  auto it = std::find(hand.begin(), hand.end(), card);
  if (it != hand.end()) {
    hand.erase(it);
  }
}

void Player::clear() {
  hand.clear();
  discarded.clear();
}


