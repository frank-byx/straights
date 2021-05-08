# Straights

Term project for CS246 - Object-Oriented Software Development at the University of Waterloo.

Straights is a four-person command line card game using a 52-card deck, playable as a hotseat game with friends or by yourself against computer opponents.

## Getting Started

Clone this repository using the following command:

```
git clone https://github.com/frank-byx/straights.git
```

Navigate to the project directory and run `make` to compile the program. Run `./straights` to start the program.

## Game Rules

Straights uses a standard 52-card deck, without the jokers. There are four players, and each player is dealt 13 cards at the beginning of each round. Ace is considered to be the lowest card in each suit, while the King is the highest.
There are four piles of cards on the table, one for each suit.

Immediately following the deal, the player with the 7 of spades goes first. This player must play the 7 of spades in the centre of the table. After the 7 of spades, the players take turns to play cards on the table. A legal play is a 7 of any suit, or a card with the same suit and adjacent rank
as another card that has already been played. The played card will be added to the appropriate pile.

When a player has no legal plays, they must discard a card in their hand, but if a player has at least one legal play in their hand, then they must make a legal play.

The round ends when all the cards have either been played or discarded. For each player, their score for the round is the sum of all the ranks of the player’s discards. Jacks, Queens, and Kings count as 11, 12, and 13 points, respectively. Each player’s game score is the sum of their scores in each round. If no player has accumulated 80 or more points at the end of a round, then the deck is reshuffled and another round begins. If at least one player has accumulated 80 points or more, the game ends. The players with the lowest score win.

## How to Play

Begin by typing "h" or "c" to indicate whether each player is a human or a computer.

There are 5 valid commands for a human player in this game:

```
play <card>
discard <card>
deck
quit
ragequit
```

`<card>` has syntax `<rank><suit>`, such as `7C` for the seven of clubs for example. For the ranks, `A` = Ace, `1` = 1, ..., `9` = 9, `T` = 10, `J` = Jack, `Q` = Queen, `K` = King. The suits are: `C` = Clubs,
`D` = Diamonds, `H` = Hearts. `S` = Spades.

`play <card>` plays the card `<card>`, and `discard <card>` discards the card `<card>`.

`deck` prints out the deck in the order that it was dealed (for debugging purposes).

`quit` quits the program, and `ragequit` changes the current human player into a computer player.
