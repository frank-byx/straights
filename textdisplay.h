#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H

#include <iostream>
#include <vector>
#include <string>
#include "card.h"
#include "info.h"
#include "observer.h"
#include "state.h"
#include "subject.h"

class TextDisplay : public Observer<Info, State> {
  int currentPlayer;
  std::string clubsDisplay;
  std::string diamondsDisplay;
  std::string heartsDisplay;
  std::string spadesDisplay;
  std::string playerHandDisplay;
  std::string legalMovesDisplay;
  std::string stateDisplay;        // message describing the last play / last discard / new round
public:
  TextDisplay();
  void notify(Subject<Info, State> &whoFrom) override;
  std::string getStateDisplay() const;
  static std::string toNotation(std::vector<Card> cards);   // convert vector of cards to notation string
  static std::string toNotation(Card card);                 // convert single card to notation string
  static std::vector<std::string> getRankNotation();        // list the rank notation symbols indexed by enumeration value
  static std::vector<std::string> getSuitNotation();        // list the suit notation symbols indexed by enumeration value
  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
