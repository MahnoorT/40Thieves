/**
 * \file Gameboard.h
 * \brief Header file for the gameboard defining the main procedures
 * \author Mahnoor Tariq, MacID: tariqm9
 * \date March 20th, 2019
*
*/

#ifndef A3_GAME_BOARD_H_
#define A3_GAME_BOARD_H_

#include "CardStack.h"
#include "CardTypes.h"

/**
* \brief This class will create a GameBoard of the solitaire game Forty Theives.
* \details This class will implement a Forty Thieves solitaire game complete with
* all of the different aspects of the game. It will allow for valid movement of cards
* around the board, will validate these moves, retrieve card stacks and determine if the game has been won.
*/
typedef std::vector<CardStackT> SeqCrdStckT;
class BoardT {
private:
  std::vector<CardT> cards;
  SeqCrdStckT tableau;
  SeqCrdStckT foundation;
  CardStackT deck;
  CardStackT waste;

  //local private functions

  SeqCrdStckT tab_deck(std::vector<CardT>);
  bool valid_tab_mv();
  bool valid_waste_mv();
  SeqCrdStckT tab_deck();
  SeqCrdStckT init_seq(unsigned int n);
  bool two_decks(std::vector<CardT> cards);

public:
  /**
  * \brief Create a Forty Thieves gamebaord
  * \details A Forty Thieves gameboard is created with a tableau of 10 cardstacks,
  * a foundation of 8 cardstacks, a deck and an empty waste stack. It will be the default
  * gameboard for the game.
  * \param cards A deck of cards containing two cards of each rank & suit is distributed
  * randomly throughout the gameboard.
  */

  BoardT(std::vector<CardT> cards);
  /**
  * \brief Moves a card from the a tableau cardstack to either another tableau cardstack
  * or a foundation cardstack.
  * \details The function will check is a move to certain category is possible and if valid,
  * will "move the card" by popping it off one stack and pushing the top onto the other.
  * \param c An input of type CategoryT (Tableau, Foundation, Waste, Deck)
  * \param n1 The index of the tableau cardstack with the card wanting to be moved
  * \param n2 The index of the destination cardstack
  */
  void tab_mv(CategoryT c, unsigned  int n1, unsigned int n2);
  /**
  * \brief Will move a card from the waste to either the tableau or the foundation
  * \details The function will check if a move is possible and if valid, will pop off
  * the card from the waste stack and push the top onto the inputted stack.
  * \param c An input of type CategoryT (Tableau, Foundation, Waste, Deck)
  * \param n The index of the destination cardstack
  */
  void waste_mv(CategoryT c, unsigned int n);
  /**
  * \brief Will move a card from the waste to either the tableau or the foundation
  * \details The function will check if a move is possible and if valid, will pop off
  * the card from the deck and push the top onto the waste stack.
  */
  void deck_mv();
  /**
  * \brief Will retrieve the stack of cards in the tableau
  * \details The function will check if the index between 0 and 10 and if valid, will return the cardstack.
  * \param i The index of the desired tableau cardstack
  * \return A vector of CardTs from the tableau.
  */
  CardStackT get_tab(int i);
  /**
  * \brief Will retrieve the stack of cards in the foundation
  * \details The function will check if the index between 0 and 8 and if valid, will return the cardstack.
  * \param i The index of the desired foundation cardstack
  * \return A vector of CardTs from the foundation.
  */
  CardStackT get_foundation(int i);
  /**
  * \brief Will retrieve the waste pile
  * \return A CardStackT of the waste pile
  */
  CardStackT get_waste();
  /**
  * \brief Will retrieve the deck
  * \return A CardStackT of the deck
  */
  CardStackT get_deck();
  /**
  * \brief Will return a bool value that checks if a move is possible
  * \details The function will check if a valid tab move, a valid foundation move
  * or a valid deck move exists. If any are true, it will return a true value infroming users that
  * a move is possible.
  * \return A boolean value of whether a move is possible in the deck
  */
  bool valid_mv_exists();
  /**
  * \brief Will return a bool value that checks if the game is won
  * \details The function will check if every foundation stack is non-empty and if the top card is a KING.
  * If true, the function will return true as these are the conditins of a complete game.
  * \return A boolean value of whether the user has won the game or not.
  */
  bool is_win_state();
  /**
  * \brief Will return a bool value that checks if a specific tableau move is possible
  * \details The function will check if a specific move from a tableau cardstack to another cardstack
  * on the gameboard is possible. It will return false if c is Waste or Deck. The function
  * also checks if n1 & n2 are within the right range.
  * \param c An input of type CategoryT (Tableau, Foundation, Waste, Deck)
  * \param n1 The index of the tableau cardstack with the card wanting to be moved
  * \param n2 The index of the destination cardstack
  * \return A boolean value of whether a tableau move is possible or not.
  */
  bool is_valid_tab_mv(CategoryT c, unsigned  int n1, unsigned int n2);
  /**
  * \brief Will return a bool value that checks if a specific waste move is possible
  * \details The function will check if a specific move from the waste pile to another cardstack
  * on the gameboard is possible. It will return false if c is Waste or Deck. The function
  * also checks if n1 is within the right range.
  * \param c An input of type CategoryT (Tableau, Foundation, Waste, Deck)
  * \param n1 The index of the desitnation cardstack.
  * \return A boolean value of whether a waste move is possible or not.
  */
  bool is_valid_waste_mv(CategoryT c, unsigned  int n1);
  /**
  * \brief Will return a bool value that checks if a deck move is possible.
  * \details The function will check if a move from the deck to the waste pile is possble
  * by checking to see if the deck is not empty.
  * \return A boolean value of whether a deck move is possible or not.
  */
  bool is_valid_deck_mv();
  
};

#endif
