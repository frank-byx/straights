#include "game.h"
#include "exception.h"
#include <random>
#include <algorithm>
#include <iostream>

const int PLAYERS = 4;

Game::Game(unsigned seed) : players(PLAYERS), table{}, scoreboard(PLAYERS), rng{seed} {
  for (int suitInt = 0; suitInt < SUITS; ++suitInt) {
    for (int rankInt = 0; rankInt < RANKS; ++rankInt) {
      deck.emplace_back(static_cast<Rank>(rankInt), static_cast<Suit>(suitInt));   // initialize deck in standard order
    }
  }
}

std::vector<Card> Game::getDeck() const {
  return deck;
}

int Game::getCurrentPlayer() const {
  return currentPlayer;
}

void Game::play(Card card) {
  std::vector<Card> legalMoves = getLegalMoves();
  if (std::find(legalMoves.begin(), legalMoves.end(), card) == legalMoves.end()) {                                // check if play is legal
    throw InvalidMoveException{};
  }
  if (table.getPile(card.getSuit()).empty() || card.comesAfter(table.getPile(card.getSuit()).back())) {           // play card on table
    table.push_back(card);
  } else {
    table.push_front(card);
  }
  players.at(currentPlayer).removeFromHand(card);                                                                 // remove card from player's hand
  setState(State{Play, currentPlayer, card});
  currentPlayer = (currentPlayer + 1) % PLAYERS;
  notifyObservers();
}

void Game::discard(Card card) {
  std::vector<Card> hand = getCurrentPlayerHand();
  if (!getLegalMoves().empty() || std::find(hand.begin(), hand.end(), card) == hand.end()) {    // check if discard is legal
    throw InvalidMoveException{};
  }
  players.at(currentPlayer).addToDiscarded(card);                                               // add card to player's discarded cards
  players.at(currentPlayer).removeFromHand(card);                                               // remove card from player's hand
  setState(State{Discard, currentPlayer, card});
  currentPlayer = (currentPlayer + 1) % PLAYERS;
  notifyObservers();
}

bool Game::roundOver() const {
  for (Player player : players) {
    if (!player.getHand().empty()) {                // check if all hands are empty
      return false;
    }
  }
  return true;
}

bool Game::gameOver() const {
  for (int score : scoreboard) {                    // check if any player has a score >= 80
    if (score >= 80) {
      return true;
    }
  }
  return false;
}

std::vector<int> Game::getWinners() const {
  int minScore = *(std::min_element(scoreboard.begin(), scoreboard.end()));   // get the smallest score
  std::vector<int> winners;
  for (int i = 0; i < PLAYERS; ++i) {
    if (scoreboard.at(i) == minScore) {
      winners.push_back(i);                                                   // find all players with the smallest score
    }
  }
  return winners;
}

std::vector<int> Game::getScoreboard() const {
  return scoreboard;
}

void Game::updateScoreboard() {
  for (int i = 0; i < PLAYERS; ++i) {
    for (Card &card : players.at(i).getDiscarded()) {
      scoreboard.at(i) += card.getRank() + 1;
    }
  }
}

void Game::newRound() {
  for (int i = 0; i < PLAYERS; ++i) {
    players.at(i).clear();                           // clear the hands and discard piles of the players
  }
  table.clear();                                     // clear the piles on the table
  std::shuffle(deck.begin(), deck.end(), rng);       // shuffle the deck
  const int DEAL = (RANKS * SUITS) / PLAYERS;
  const Card firstCard{Seven, Spades};
  for (int i = 0; i < DEAL * PLAYERS; ++i) {
    players.at(i / DEAL).addToHand(deck.at(i));      // deal the cards
    if (deck.at(i) == firstCard) {
      currentPlayer = i / DEAL;                      // find the first player
    }
  }
  setState(State{NewRound, 0, Card{Ace,Clubs}});
  notifyObservers();
}

std::vector<Card> Game::getLegalMoves() const {
  std::vector<Card> legalMoves;
  std::vector<Card> hand = players.at(currentPlayer).getHand();
  if (count(hand.begin(), hand.end(), Card{Seven, Spades})) {    // the first player must play 7S
    legalMoves.emplace_back(Seven, Spades);
    return legalMoves;
  }
  for (Card &card : hand) {
    std::vector<Card> pile = table.getPile(card.getSuit());
    if (card.getRank() == Seven) {                               // otherwise any other 7's are legal
      legalMoves.push_back(card);
    }
    if (!pile.empty()) {
      if (card.comesAfter(pile.back()) || card.comesBefore(pile.front())) {   // any adjacent cards are legal
        legalMoves.push_back(card);
      }
    }
  }
  return legalMoves;
}

std::vector<Card> Game::getCurrentPlayerHand() const {
  return players.at(currentPlayer).getHand();
}

std::vector<std::vector<Card>> Game::getPlayerDiscards() const {
  std::vector<std::vector<Card>> discards;
  for (Player player : players) {
    discards.push_back(player.getDiscarded());
  }
  return discards;
}

Info Game::getInfo() const {
  return Info{currentPlayer, table.getPile(Clubs), table.getPile(Diamonds), table.getPile(Hearts), table.getPile(Spades), players.at(currentPlayer).getHand(), getLegalMoves()};
}
