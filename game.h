#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "table.h"
#include "state.h"
#include "info.h"
#include "subject.h"
#include <memory>
#include <vector>
#include <random>

extern const int PLAYERS;

class Game : public Subject<Info,State> {
  int currentPlayer;                                          // 0 = Player1, 1 = Player2, 2 = Player3, 3 = PLayer4
  std::vector<Player> players;                                // index follows the same convention above
  Table table;
  std::vector<Card> deck;
  std::vector<int> scoreboard;                                // index follows the same convention above
  std::default_random_engine rng;
public:
  Game(unsigned seed);
  std::vector<Card> getDeck() const;
  int getCurrentPlayer() const;
  void play(Card card);                                       // plays card from current player's hand
  void discard(Card card);                                    // discards card from current player's hand
  bool roundOver() const;
  bool gameOver() const;
  std::vector<int> getWinners() const;
  std::vector<int> getScoreboard() const;
  void updateScoreboard();                                    // must call at the end of every round
  void newRound();                                            // must call at the start of every round
  std::vector<Card> getLegalMoves() const;                    // get legal moves for current player
  std::vector<Card> getCurrentPlayerHand() const;             // get hand of current player
  std::vector<std::vector<Card>> getPlayerDiscards() const;   // get discard piles of ALL players
  virtual Info getInfo() const override;
};

#endif
