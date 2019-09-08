/**
 * \file Gameboardtest
 * \brief Unit testing for the GameBaord
 * \author Mahnoor Tariq, MacID: tariqm9
 * \date March 25th, 2019
*
*/

#include "catch.h"
#include "GameBoard.h"
#include "CardTypes.h"
#include "Stack.h"

#include <stdexcept>
#include <iostream>

TEST_CASE("Test for GameBoard", "[Gameboard]") {
  std::vector<CardT> d;
  for (RankT rank = ACE; rank <= KING; rank++) {
    for (unsigned int suit = 0; suit < 4; suit++) {
      CardT n = { static_cast<SuitT>(suit), rank };
      d.push_back(n);
      d.push_back(n);
    }
  }

  BoardT Board(d);

  SECTION("Test Gameboard constructor - 1") {

    //Checks the size of every tableau, the top cards which are one of two suits, and
    // the rank of those cards.
    for (int i = 0; i < 10; i++) {
      CardStackT tab = Board.get_tab(i);
      REQUIRE(tab.size() == 4);
      if (i%2 == 0) {REQUIRE(tab.top().s == Diamond);REQUIRE(tab.top().r == (i+2)/2);}
      if (i%2 == 1) {REQUIRE(tab.top().s == Spade);}

    }

    CardStackT deck = Board.get_deck();
    //The deck should contain the rest of the cards, so the last card pushed was KING of Spades
    REQUIRE(deck.top().r == KING);
    REQUIRE(deck.top().s == Spade);

    //All foundation stacks should be empty.
    for (int i = 0; i < 8; i++) {
      CardStackT foundation = Board.get_foundation(i);
      REQUIRE(foundation.size() ==  0);
    }
    //The waste should be empty.
    CardStackT waste = Board.get_waste();
    REQUIRE(waste.size() == 0);

  }

  SECTION("Test Gameboard Constructor - 2") {
    std::vector<CardT> d2;
    CardT n = { static_cast<SuitT>(Spade), 5};
    d2.push_back(n);
    REQUIRE_THROWS_AS(BoardT(d2), std::invalid_argument);
  }

  SECTION("is_valid_tab_mv - 1") {
    //Can't move from tableau to deck/waste
    REQUIRE(Board.is_valid_tab_mv(Waste, 0, 0) == false);
    REQUIRE(Board.is_valid_tab_mv(Deck, 0, 0) == false);
    //Can't move a tableau to itself.
    REQUIRE(Board.is_valid_tab_mv(Tableau, 0, 0) == false);
    //Moves an ACE to an empty foundation
    REQUIRE(Board.is_valid_tab_mv(Foundation, 0, 0) == true);
    //Can't move a non-ACE to an empty foundation
    REQUIRE(Board.is_valid_tab_mv(Foundation, 5, 0) == false);
    //Can move a card in a tableau stack to another with the same suit and a higher rank by one.
    //Ace of Diamonds moved to 1 of Diamonds
    REQUIRE(Board.is_valid_tab_mv(Tableau, 0, 2) == true);
    //Can't move cards of different suits onto one another
    //Ace of Diamonds to 1 of Spades
    REQUIRE(Board.is_valid_tab_mv(Tableau, 0, 3) == false);
    //Can't move cards of same suits but wrong onto onto one another
    //Ace of Diamonds to 2 of Diamonds
    REQUIRE(Board.is_valid_tab_mv(Tableau, 0, 4) == false);
  }

  SECTION("is_valid_tab_mv - 2") {
    //Out of range index values
    REQUIRE_THROWS_AS(Board.is_valid_tab_mv(Tableau, 45, 9), std::out_of_range);
    REQUIRE_THROWS_AS(Board.is_valid_tab_mv(Foundation, -3, 0), std::out_of_range);
  }

  SECTION("is_valid_deck_mv - 1") {
    //Since the deck is full, we can move to the waste pile.
    REQUIRE(Board.is_valid_deck_mv() == true);
    for (int i = 0; i < 64; i++) {
      Board.deck_mv();
    }
    //Emptied deck through for-loop, deck is empty so no move possible
    REQUIRE(Board.is_valid_deck_mv() == false);
  }

  SECTION("is_valid_waste_mv - 1") {
    std::vector<CardT> e;
    for (RankT rank = KING; rank >= ACE; rank--) {
      for (unsigned int suit = 0; suit < 4; suit++) {
        CardT n = { static_cast<SuitT>(suit), rank };
        e.push_back(n);
        e.push_back(n);
      }
    }
    BoardT Board(e);
    //Can't move from waste to deck/itself
    REQUIRE(Board.is_valid_waste_mv(Waste, 0) == false);
    REQUIRE(Board.is_valid_waste_mv(Deck, 0) == false);
    //Waste to Foundation: Ace card to empty pile
    //std::cout << Board.get_waste
    Board.deck_mv();
    REQUIRE(Board.is_valid_waste_mv(Foundation, 0) == true);
    //Moving all aces to the foundation to allow for a waste -> non-empty foundation move
    Board.waste_mv(Foundation, 0);
    for (int i = 1; i < 8; i++) {
      Board.deck_mv();
      Board.waste_mv(Foundation, i);
    }
    //Waste to Foundation: Same suit but one rank higher.
    Board.deck_mv();
    REQUIRE(Board.is_valid_waste_mv(Foundation, 0) == true);
    //Waste to Foundation: Can't move different suits/wrong ranked cards onto one another
    Board.deck_mv();
    REQUIRE(Board.is_valid_waste_mv(Foundation, 4) == false);
    //Waste to Tableau: Move not possible
    REQUIRE(Board.is_valid_waste_mv(Tableau, 0) == false);
  }

  SECTION("is_valid_waste_mv - 2") {
    //Out of range index values
    REQUIRE_THROWS_AS(Board.is_valid_waste_mv(Tableau, -50), std::out_of_range);
    REQUIRE_THROWS_AS(Board.is_valid_waste_mv(Foundation, 90), std::out_of_range);
  }

  SECTION("get_tab - 1") {
    BoardT Board(d);
    //Even though its been tested when we call the constructor, we can show it again in a similar manner.
    //get_tab grabs each cardstack in the sequence and returns it
    for (int i = 0; i < 10; i++) {
      CardStackT tab = Board.get_tab(i);
      if (i%2 == 0) {REQUIRE(tab.top().s == Diamond); REQUIRE(tab.top().r == (i+2)/2);}
      if (i%2 == 1) {REQUIRE(tab.top().s == Spade);}
    }
  }

  SECTION("get_tab - 2") {
    //Throws exception if index is out of out_of_range
    REQUIRE_THROWS_AS(Board.get_tab(90), std::bad_alloc);
    REQUIRE_THROWS_AS(Board.get_tab(-5), std::bad_alloc);
  }

  SECTION("get_foundation - 1") {
    BoardT Board(d);
    //Initally empty
    REQUIRE(Board.get_foundation(0).size() == 0);
    Board.tab_mv(Foundation, 0, 0);
    //Foundation has one card
    REQUIRE(Board.get_foundation(0).size() == 1);
    REQUIRE(Board.get_foundation(0).top().r == ACE);
    REQUIRE(Board.get_foundation(0).top().r == Diamond);
  }

  SECTION("get_foundation - 2") {
    REQUIRE_THROWS_AS(Board.get_foundation(32), std::bad_alloc);
    REQUIRE_THROWS_AS(Board.get_foundation(-4), std::bad_alloc);
  }

  SECTION("get_deck - 1") {
    BoardT Board(d);
    //Initally full with 64 cards
    REQUIRE(Board.get_deck().size() == 64);
    Board.deck_mv();
    //Board moved so size decreased
    REQUIRE(Board.get_deck().size() == 63);
  }

  SECTION("get_waste - 1") {
    BoardT Board(d);
    //Initally empty
    REQUIRE(Board.get_waste().size() == 0);
    Board.deck_mv();
    //Board moved so size increased.
    REQUIRE(Board.get_waste().size() == 1);
  }

  SECTION("valid_mv_exists - 1") {
    std::random_shuffle(d.begin(), d.end());
    BoardT Board(d);
    //When a board is created, the a move will definitely exists atleast from the deck to the waste.
    REQUIRE(Board.valid_mv_exists() == true);
    for (int i = 0; i < 64; i++) {
      Board.deck_mv();
    }
    //This is taking a chance since the deck is randomly shuffled that after the deck has been moved, no move exists.
    REQUIRE(Board.valid_mv_exists() == false);
  }

  SECTION("tab_mv - 1") {
    BoardT Board(d);
    //Checks to see if tableau card has moved to another tableau
    CardT card1 = Board.get_tab(0).top();
    Board.tab_mv(Tableau, 0, 2);
    CardT card2 = Board.get_tab(2).top();
    REQUIRE(card1.r == card2.r);
    REQUIRE(card1.s == card2.s);

    //Checks to see if a tableau has moved to foundation
    CardT card3 = Board.get_tab(1).top();
    Board.tab_mv(Foundation, 1, 2);
    CardT card4 = Board.get_foundation(2).top();
    REQUIRE(card3.r == card4.r);
    REQUIRE(card3.s == card4.s);
  }

  SECTION("tab_mv - 2") {
    //Catches a move thats not possible
    REQUIRE_THROWS_AS(Board.tab_mv(Tableau, 0, 8), std::invalid_argument);

    //Catches a move out of out_of_range & invalid
    REQUIRE_THROWS_AS(Board.tab_mv(Waste, 0, 8), std::invalid_argument);
    REQUIRE_THROWS_AS(Board.tab_mv(Tableau, 0, -3), std::out_of_range);
  }

  SECTION("deck_mv - 1") {
    //Checks if the top card in the deck has moved to the waste pile
    BoardT board(d);
    CardT card1 = Board.get_deck().top();
    Board.deck_mv();
    CardT card2 = Board.get_waste().top();
    REQUIRE(card1.r == card2.r);
    REQUIRE(card1.s == card2.s);
  }

  SECTION("deck_mv - 2") {
    //Checks to see if deck_mv error is caught when moving an empty pile
    BoardT board(d);
    for (int i = 0; i < 64; i++) {
      Board.deck_mv();
    }
    REQUIRE_THROWS_AS(Board.deck_mv(), std::invalid_argument);
  }

  SECTION("waste_mv - 1") {
    std::vector<CardT> e;
    for (RankT rank = KING; rank >= ACE; rank--) {
      for (unsigned int suit = 0; suit < 4; suit++) {
        CardT n = { static_cast<SuitT>(suit), rank };
        e.push_back(n);
        e.push_back(n);
      }
    }
    BoardT Board(e);
    Board.deck_mv();

    //Checks to see if waste card has moved to another the foundation
    CardT card1 = Board.get_waste().top();
    Board.waste_mv(Foundation, 2);
    CardT card2 = Board.get_foundation(2).top();
    REQUIRE(card1.r == card2.r);
    REQUIRE(card1.s == card2.s);

  }

  SECTION("waste_mv - 2") {
    //Catches a move thats not possible
    REQUIRE_THROWS_AS(Board.waste_mv(Tableau, 8), std::invalid_argument);

    //Catches a move out of out_of_range & invalid
    REQUIRE_THROWS_AS(Board.waste_mv(Waste, 8), std::invalid_argument);
    REQUIRE_THROWS_AS(Board.waste_mv(Tableau, -3), std::out_of_range);

  }





}
