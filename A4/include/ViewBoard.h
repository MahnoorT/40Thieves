/**
 * \file ViewBoard.h
 * \brief Header file of the View module the Read, Write and show functions are defined.
 * \author Mahnoor Tariq, MacID: tariqm9
 * \date April 10th, 2019
*
*/

#ifndef VIEW_BOARD_H
#define VIEW_BOARD_H

#include "BoardTypes.h"
#include "GameBoard.h"
#include <vector>
#include <string>

/**
* \brief Reads a gameboard file that's formatted to mimic the start of a board
* \details Reads the input file and allocates every stated alive memeber to a double-vector sequence which then
* creates the abstract data type GridT
* \param An input file containing the correct game format
* \return A GridT object initialized with a game state
*/
GridT Read(std::string file);
/**
* \brief Displays the state of the board on the module
* \details Takes in gameboard grid and iterates through every cell to show its state.
* \param A GridT ADT of a gameboard
*/
void show(GridT grid);
/**
* \brief Writes out the state of the board to a file
* \details Takes in gameboard grid and iterates through every cell to write out its state.
* \param A GridT ADT of a gameboard
*/
void write(GridT grid);



#endif
