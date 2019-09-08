/**
 * \file Main
 * \brief Acts as a controller second to testing, used for debugging in the code.
 * \author Mahnoor Tariq, MacID: tariqm9
 * \date April 12th, 2019
*
*/

#include "BoardTypes.h"
#include "GameBoard.h"
#include "ViewBoard.h"

#include <iostream>
#include <vector>

int main() {
  std::cout << "Hello World!\n";

  //gridt2 = gridt.update();
  GridT size = Read("src/readgrid.txt");
  //gridt2 = Read();
  //std::cout << "Hello World!\n";
  show(size);
  std::cout << std::endl;


  size = size.update();
  show(size);
  std::cout << std::endl;
  std::cout << std::endl;

  size = size.update();
  show(size);
  write(size);

  int count = size.stateCount(Alive);
  int count2 = size.stateCount(Dead);
  std::cout << count << count2 << std::endl;

  /**
  size = size.update();
  show(size);
  write(size);


  size = size.update();
  show(size);
  write(size);
  */
}
