/**
 * \file GameBoard
 * \brief Header file that outlines the instances of the GridT class
 * \author Mahnoor Tariq, MacID: tariqm9
 * \date April 12th, 2019
*
*/

#ifndef A4_BOARD_GAME_H
#define A4_BOARD_GAME_H

#include "BoardTypes.h"
#include <vector>

/**
* \brief GameBoard ADT used to represent a single gameboard state.
* \details This modules created an initialized grid of cellstates of either dead/alive and simulates Conway's Game of Life.
* The update instance goes to the next state of a board depending on conway's rules. The other functions are all used
* to aid in the update of the board.
*/

class GridT {
private:

  std::vector<std::vector<CellState> > grid;
  std::vector<std::vector<CellState> > init_seq(int n);

public:
  /**
  * \brief Creates a gameboard grid
  * \details Takes in a vector of a vector of Cellstates that are in the first game state and initializes it to an ADT.
  * \param The initial state of the board
  * \return GridT ADT
  */
  GridT(std::vector<std::vector<CellState> > grid);
  /**
  * \brief Updates the state of the game
  * \details Iterates through every cell and updates its state of dead/alive depending on its neighbours state.
  * \return An update GridT ADT
  */
  GridT update();
  /**
  * \brief Checks the state of a cell
  * \param n1 the row number of the cell
  * \param n2 the col number of the cell
  * \return An update GridT ADT
  */

  CellState checkCell(int n1, int n2);
  /**
  * \brief Checks the states of all cells and returns a number
  * \details Iterate through every cell in the baord and record whether its alive or dead
  * \param state a cell state - Alive/Dead
  * \return The number of alive or dead cells
  */
  int stateCount(CellState state);
  /**
  * \brief Checks the neighbouring states of a cell and returns the number of alive cells
  * \param GridT the GridT ADT
  * \param row the row number of the cell
  * \param col the col number of the cell
  * \return The number of adjacent alive cells
  */
  int neighbourCnt(GridT grid, int row, int col);

};

#endif
