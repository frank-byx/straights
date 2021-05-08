#include "client.h"
#include "abstractcpu.h"
#include "basiccpu.h"
#include "exception.h"
#include <iostream>
#include <string>
#include <memory>
#include <algorithm>
#include <vector>
#include <iterator>

Client::Client(unsigned seed) : game{seed}, td{}, cpus(4) {
  game.attach(&td);
  // Ask if players are humans or CPU's
  for (int i = 0; i < PLAYERS; ++i) {
    std::cout << "Is Player" << i + 1 << " a human (h) or a computer (c)?" << std::endl;
    char input;
    std::cout << ">";
    std::cin >> input;
    if (input == 'c') {
      std::unique_ptr<AbstractCPU> temp = std::make_unique<BasicCPU>(&game, i);
      cpus.at(i).swap(temp);
    }
  }
}

void Client::run() {
  bool quit = false;
  while (!game.gameOver() && !quit) {
    game.newRound();                                      // initialize first round
    std::cout << td.getStateDisplay() << std::endl;       // print new round message
    std::cout << td;                                      // print game info for first player
    while (!game.roundOver() && !quit) {
      if(cpus.at(game.getCurrentPlayer())) {              // check if CPU
        std::cout << ">";
        cpus.at(game.getCurrentPlayer())->play();         // CPU play's
        std::cout << td.getStateDisplay() << std::endl;   // print move message
      } else {
        while (true) {
          std::cout << ">";
          std::string command;
          std::cin >> command;
          if (command == "play" || command == "discard") {
            std::string cardInput;
            std::cin >> cardInput;
            std::vector<std::string> rankNotation = TextDisplay::getRankNotation();
            std::vector<std::string> suitNotation = TextDisplay::getSuitNotation();
            if (std::find(rankNotation.begin(), rankNotation.end(), cardInput.substr(0,1)) == rankNotation.end()) {
              std::cout << "Invalid card rank entered. Try again." << std::endl;
              continue;
            }
            if (std::find(suitNotation.begin(), suitNotation.end(), cardInput.substr(1,1)) == suitNotation.end()) {
              std::cout << "Invalid card suit entered. Try again." << std::endl;
              continue;
            }
            Rank rank = static_cast<Rank>(std::distance(rankNotation.begin(), std::find(rankNotation.begin(), rankNotation.end(), cardInput.substr(0,1))));
            Suit suit = static_cast<Suit>(std::distance(suitNotation.begin(), std::find(suitNotation.begin(), suitNotation.end(), cardInput.substr(1,1))));
            Card card{rank, suit};                                // construct human player's card
            if (command == "play") {
              try {
                game.play(card);                                  // play human player's card
                std::cout << td.getStateDisplay() << std::endl;   // print move message
                break;
              } catch (InvalidMoveException) {
                std::cout << "This is not a legal play." << std::endl;
              }
            } else {
              try {
                game.discard(card);                               // discard human player's card
                std::cout << td.getStateDisplay() << std::endl;   // print move message
                break;
              } catch (InvalidMoveException) {
                std::cout << "You have a legal play. You may not discard." << std::endl;
              }
            }
          } else if (command == "deck") {                                // print the deck
            std::string deck = TextDisplay::toNotation(game.getDeck());
            int d = 3 * RANKS - 1;
            for (int i = 0; i < SUITS; ++i) {
              std::cout << deck.substr(1 + i + i * d, d) << std::endl;
            }
          } else if (command == "quit") {                                // quit the game
            quit = true;
            break;
          } else if (command == "ragequit") {                            // human player ragequits
            int currentPlayer = game.getCurrentPlayer();
            std::unique_ptr<AbstractCPU> temp = std::make_unique<BasicCPU>(&game, currentPlayer);
            cpus.at(currentPlayer).swap(temp);
            std::cout << "Player" << currentPlayer + 1 << " ragequits. A computer will now take over." << std::endl;
            break;
          } else {
            std::cout << "Invalid command entered. Try again." << std::endl;
          }
        }
      }
      // reached end of turn
      if (!game.roundOver() && !quit) {
        std::cout << td;   // print game info for next player
      }
    }
    // reached end of round
    if (!quit) {
      std::vector<std::vector<Card>> playerDiscards = game.getPlayerDiscards();
      std::vector<int> oldScoreboard = game.getScoreboard();
      game.updateScoreboard();
      std::vector<int> newScoreboard = game.getScoreboard();
      for (int i = 0; i < PLAYERS; ++i) {   // print score calculations for each player
        std::cout << "Player" << i + 1 << "'s discards:" << TextDisplay::toNotation(playerDiscards.at(i)) << std::endl;
        std::cout << "Player" << i + 1 << "'s score: " << oldScoreboard.at(i) << " + " << newScoreboard.at(i) - oldScoreboard.at(i) << " = " << newScoreboard.at(i) << std::endl;
      }
    }
  }
  // reached end of game
  if (!quit) {
    std::vector<int> winners = game.getWinners();
    for (int player : winners) {
      std::cout << "Player" << player + 1 << " wins!" << std::endl;   // print winners
    }
  }
}
