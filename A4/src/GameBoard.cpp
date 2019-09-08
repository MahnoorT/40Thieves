/**
 * \file GameBoard
 * \brief Creates the Board for the game and
 * \author Mahnoor Tariq, MacID: tariqm9
 * \date April 9th, 2019
*
*/
#include "GameBoard.h"
#include "BoardTypes.h"
#include <iostream>
#include <stdexcept>
#include <vector>

GridT::GridT(std::vector<std::vector<CellState> > grid) {
  this->grid = grid;
}

//Running through one simulation of the board game
GridT GridT::update() {
  std::vector<std::vector<CellState> > temp = init_seq(BOARDLENGTH);
  for (int row = 0; row < BOARDLENGTH; row++) {
    for (int col = 0; col < BOARDLENGTH; col++) {
        int neighbours = GridT::neighbourCnt(this->grid, row, col);
        CellState isAlive = this->grid[row][col];
        if (isAlive == Alive && neighbours < 2) {
          temp[row][col] = Dead;
        }
        else if (isAlive == Alive && (neighbours == 2 || neighbours == 3)) {
          temp[row][col] = Alive;
        }
        else if (isAlive == Alive && neighbours > 3) {
          temp[row][col] = Dead;
        }
        else if (isAlive == Dead && neighbours == 3) {
          temp[row][col] = Alive;
        }
        else {
          temp[row][col] = Dead;
        }
    }
  }
  return GridT(temp);
}


//Checking the neighbours of the cell
int GridT::neighbourCnt(GridT grid, int row, int col) {
  if (row < 0 || row >= BOARDLENGTH || col < 0 || col >= BOARDLENGTH) {
    throw std::invalid_argument("Indexes out of range");
  }
  int neighbours = 0;
  for(int c = -1; c < 2; c++){
    for(int d = -1; d < 2; d++){
      if(!(c == 0 && d == 0)){
        CellState isAlive = grid.checkCell((row+c), (col+d));
        if(isAlive == Alive) {++neighbours;}
      }
    }
  }
  return neighbours;
}


//Check the state of the current cell
CellState GridT::checkCell(int n1, int n2) {
  if (n1 < 0 || n1 >= BOARDLENGTH || n2 < 0 || n2 >= BOARDLENGTH) {
    return Dead;
  }
  return this->grid[n1][n2];
}

//Initializing an empty grid.
std::vector<std::vector<CellState> > GridT::init_seq(int n) {

  if (n != BOARDLENGTH) {throw std::invalid_argument("Wrong length");}

  std::vector<std::vector<CellState> > empty;
  for (int i = 0; i < n; i++) {
    std::vector<CellState> temp;
    for (int j = 0; j < n; j++) {
      CellState x = Dead;
      temp.push_back(x);
    }
    empty.push_back(temp);
  }

  return empty;
}

int GridT::stateCount(CellState state) {
  int count = 0;
  for (int row = 0; row < BOARDLENGTH; row++) {
    for (int col = 0; col < BOARDLENGTH; col++) {
      if (checkCell(row, col) == state) {count++;}
    }
  }
  return count;
}
