/**
 * \file Gameboardtest
 * \brief Unit testing for the GameBaord
 * \author Mahnoor Tariq, MacID: tariqm9
 * \date April 12th, 2019
*
*/

#include "catch.h"
#include "GameBoard.h"
#include "BoardTypes.h"
#include "ViewBoard.h"

#include <stdexcept>
#include <iostream>

TEST_CASE("Test for GameBoard", "[Gameboard]") {

    GridT gameRead = Read("src/readgrid.txt");
      
    SECTION("Testing CheckCell") {
      REQUIRE(gameRead.checkCell(0, 0) != Dead);
      REQUIRE(gameRead.checkCell(7, 0) == Dead);
      REQUIRE(gameRead.checkCell(21, 4) != Alive);
      REQUIRE(gameRead.checkCell(13, 24) == Alive);
    }

    SECTION("Testing CheckCell Edge Cases") {
      REQUIRE(gameRead.checkCell(-8, 9) == Dead);
      REQUIRE(gameRead.checkCell(0, 35) == Dead);
    }

    SECTION("Testing neighbourCnt") {
      REQUIRE(gameRead.neighbourCnt(gameRead, 0, 0) == 3);
      REQUIRE(gameRead.neighbourCnt(gameRead, 7, 1) == 0);
    }

    SECTION("Testing neighbourCnt - Exceptions") {
      REQUIRE_THROWS_AS(gameRead.neighbourCnt(gameRead, -3, 31), std::invalid_argument);
      REQUIRE_THROWS_AS(gameRead.neighbourCnt(gameRead, 7, 31), std::invalid_argument);
    }

    SECTION("Testing stateCount") {
      REQUIRE(gameRead.stateCount(Dead) == 603);
      REQUIRE(gameRead.stateCount(Alive) == 22);
    }

    SECTION("Testing Initial State") {

      //Checking cell states
      REQUIRE(gameRead.checkCell(0, 0) == Alive);
      REQUIRE(gameRead.checkCell(4, 8) == Dead);
      REQUIRE(gameRead.checkCell(13, 24) == Alive);
      REQUIRE(gameRead.checkCell(2, 1) == Dead);

      //Initial values
      REQUIRE(gameRead.stateCount(Dead) == 603);
      REQUIRE(gameRead.stateCount(Alive) == 22);

      //In the next iteration:
      REQUIRE(gameRead.neighbourCnt(gameRead, 0, 0) == 3); //Stay alive
      REQUIRE(gameRead.neighbourCnt(gameRead, 4, 8) == 0); //Stay dead
      REQUIRE(gameRead.neighbourCnt(gameRead, 13, 24) == 1); //Should die
      REQUIRE(gameRead.neighbourCnt(gameRead, 2, 1) == 3); //Should come alive
    }

    gameRead = gameRead.update();
    SECTION("Testing First Iteration") {

      //Checking if the cells die or come alive correctly
      REQUIRE(gameRead.checkCell(0, 0) == Alive);
      REQUIRE(gameRead.checkCell(4, 8) == Dead);
      REQUIRE(gameRead.checkCell(13, 24) == Dead);
      REQUIRE(gameRead.checkCell(2, 1) == Alive);

      //Numer of Alive & Dead Cells counted for
      REQUIRE(gameRead.stateCount(Dead) == 607);
      REQUIRE(gameRead.stateCount(Alive) == 18);

      //In the next iteration:
      REQUIRE(gameRead.neighbourCnt(gameRead, 0, 0) == 1); //Should die
      REQUIRE(gameRead.neighbourCnt(gameRead, 4, 8) == 0); //Stay dead
      REQUIRE(gameRead.neighbourCnt(gameRead, 13, 24) == 2); //Stay dead
      REQUIRE(gameRead.neighbourCnt(gameRead, 2, 1) == 2); //Should stay alive
    }

    gameRead = gameRead.update();
    SECTION("Testing Second Iteration") {

      //Checking if the cells die or come alive correctly
      REQUIRE(gameRead.checkCell(0, 0) == Dead);
      REQUIRE(gameRead.checkCell(4, 8) == Dead);
      REQUIRE(gameRead.checkCell(13, 24) == Dead);
      REQUIRE(gameRead.checkCell(2, 1) == Alive);

      //Numer of Alive & Dead Cells counted for
      REQUIRE(gameRead.stateCount(Dead) == 613);
      REQUIRE(gameRead.stateCount(Alive) == 12);

    }

}
