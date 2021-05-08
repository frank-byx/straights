#ifndef STATE_H
#define STATE_H

#include "card.h"

// State contains information about the last change that occured in the game.
// State either describes a play, a discard, or the start of a new round.
// The fields player and card are not relevant if the action is NewRound.

enum Action { Play, Discard, NewRound };

struct State {
  Action action;
  int player;
  Card card;
};

#endif
