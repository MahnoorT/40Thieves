/**
 * \file CardStacktest
 * \brief Unit testing for the CardStackT ADT
 * \author Mahnoor Tariq, MacID: tariqm9
 * \date March 25th, 2019
*
*/

#include "catch.h"
#include "GameBoard.h"
#include "CardTypes.h"
#include "Stack.h"
#include <stdexcept>

TEST_CASE("Test for Stack", "[CardStack]") {

  std::vector<CardT> d;
  for (RankT rank = ACE; rank <= KING; rank++) {
    for (unsigned int suit = 0; suit < 4; suit++) {
      CardT n = { static_cast<SuitT>(suit), rank };
      d.push_back(n);
      d.push_back(n);
    }
  }


  SECTION("constructor for Stack") {
    //checks to see if the stack is created and by checking top card
    CardStackT Stack(d);
    REQUIRE(Stack.top().r == KING);

  }

  SECTION("testing size - 1") {
    //getting the size of a non-empty stack
    CardStackT Stack1(d);
    unsigned int len = Stack1.size();
    REQUIRE(len == 104);
  }

  SECTION("testing size - 2") {
    //getting the size of an empty stack
    std::vector<CardT> emptyv;
    CardStackT Stack2(emptyv);
    unsigned int len = Stack2.size();
    REQUIRE(len == 0);

  }

  SECTION("testing push - 1") {
    //push a CardT onto the stack and checking size + correct card
    std::vector<CardT> d;
    CardStackT push1(d);
    CardT n = { static_cast<SuitT>(Diamond), KING};
    push1.push(n);
    REQUIRE(push1.size() == 1);
    REQUIRE(push1.top().r == KING);
    REQUIRE(push1.top().s == Diamond);

  }

  SECTION("testing push - 2") {
    //pushing multiple CardTs onto the stack and checking size + correct card
    std::vector<CardT> d;
    CardStackT push2(d);
    for (RankT rank = ACE; rank <= KING; rank++) {
      for (unsigned int suit = 0; suit < 4; suit++) {
        CardT n = { static_cast<SuitT>(suit), rank };
        push2.push(n);
      }
    }
    REQUIRE(push2.size() == 52);
    REQUIRE(push2.top().r == KING);
    REQUIRE(push2.top().s == Spade);
  }

  SECTION("testing pop - 1") {
    //pops the top of a stack and checks the size to see if the item was removed
    CardStackT pop1(d);
    pop1 = pop1.pop();
    REQUIRE(pop1.size() == 103);

  }

  SECTION("testing pop - 2") {
    //checks exception when pop is called on an empty stack
    std::vector<CardT> d;
    CardStackT pop1(d);
    REQUIRE_THROWS_AS(pop1.pop(), std::out_of_range);

  }

  SECTION("testing top - 1") {
    //checks to see if the top card is correct
    std::vector<CardT> d;
    d.push_back({static_cast<SuitT>(Spade), KING});
    CardStackT Stack(d);
    REQUIRE(Stack.top().r == KING);
    REQUIRE(Stack.top().s == Spade);

  }

  SECTION("testing top - 2") {
    //checks to see if the top card is correct
    std::vector<CardT> d;
    CardStackT Stack(d);
    REQUIRE_THROWS_AS(Stack.top(), std::out_of_range);

  }
  SECTION("testing toSeq") {
    //checks to see if the stack can be converted back into a Seq of CardT
    std::vector<CardT> d;
    d.push_back({static_cast<SuitT>(Spade), KING});
    CardStackT Stack(d);
    std::vector<CardT> d2 = Stack.toSeq();
    REQUIRE(d[1].r == d2[1].r);

  }

}
