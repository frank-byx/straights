#include "textdisplay.h"

using namespace std;

TextDisplay::TextDisplay()
  :  clubsDisplay{""},
     diamondsDisplay{""},
     heartsDisplay{""},
     spadesDisplay{""},
     playerHandDisplay{""},
     legalMovesDisplay{""},
     stateDisplay{""}
  {}

void TextDisplay::notify(Subject<Info, State> &whoFrom) {
  State state = whoFrom.getState();
  Info info = whoFrom.getInfo();
  if (state.action == Play) {                            // handle a card play
    if (state.card.getSuit() == Clubs) {
      clubsDisplay = toNotation(info.clubsPile);
    } else if (state.card.getSuit() == Diamonds) {
      diamondsDisplay = toNotation(info.diamondsPile);
    } else if (state.card.getSuit() == Hearts) {
      heartsDisplay = toNotation(info.heartsPile);
    } else if (state.card.getSuit() == Spades) {
      spadesDisplay = toNotation(info.spadesPile);
    }
    stateDisplay = "Player" + std::to_string(state.player + 1) + " plays " + toNotation(state.card) + ".";
  } else if (state.action == Discard) {                  // handle a card discard
    stateDisplay = "Player" + std::to_string(state.player + 1) + " discards " + toNotation(state.card) + ".";
  } else if (state.action == NewRound) {                 // handle a new round
    clubsDisplay = toNotation(info.clubsPile);
    diamondsDisplay = toNotation(info.diamondsPile);
    heartsDisplay = toNotation(info.heartsPile);
    spadesDisplay = toNotation(info.spadesPile);
    stateDisplay = "A new round begins. It's Player" + std::to_string(info.currentPlayer + 1) + "'s turn to play.";
  }
  playerHandDisplay = toNotation(info.playerHand);
  legalMovesDisplay = toNotation(info.legalMoves);
}

std::string TextDisplay::getStateDisplay() const {
  return stateDisplay;
}

std::ostream &operator<<(std::ostream &out, const TextDisplay &td) {
  out << "Cards on the table:" << std::endl;
  out << "Clubs:" << td.clubsDisplay << std::endl;
  out << "Diamonds:" << td.diamondsDisplay << std::endl;
  out << "Hearts:" << td.heartsDisplay << std::endl;
  out << "Spades:" << td.spadesDisplay << std::endl;
  out << "Your hand:" << td.playerHandDisplay << std::endl;
  out << "Legal plays:" << td.legalMovesDisplay << std::endl;
  return out;
}

std::string TextDisplay::toNotation(std::vector<Card> cards) {
  std::string notation = "";
  for (Card &card : cards) {
    notation += " " + toNotation(card);
  }
  return notation;
}

std::string TextDisplay::toNotation(Card card) {
  return getRankNotation().at(card.getRank()) + getSuitNotation().at(card.getSuit());
}

std::vector<std::string> TextDisplay::getRankNotation() {
  return vector<std::string>{"A", "2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K"};
}

std::vector<std::string> TextDisplay::getSuitNotation() {
  return vector<std::string>{"C", "D", "H", "S"};
}
