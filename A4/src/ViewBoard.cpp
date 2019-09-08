/**
 * \file ViewBoard
 * \brief Implementation of the View module where it reads from a file, writes to a file and prints ASCII display.
 * \author Mahnoor Tariq, MacID: tariqm9
 * \date April 10th, 2019
*
*/

#include "GameBoard.h"
#include "BoardTypes.h"
#include "ViewBoard.h"

#include <stdexcept>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

GridT Read(std::string file) {

  std::vector<std::vector<CellState> > empty;
  string line;
	ifstream infile;

	infile.open(file);
  while (getline(infile, line)) {
      std::vector<CellState> temp;
      for(unsigned int i = 0; i < line.size(); ++i) {
        if (i != line.size() - 3) {
          if (line[i] == '[' && line[i+1] == ' ' && line[i+2] == ']') {
            temp.push_back(Dead);
          }
          else if (line[i] == '[' && line[i+1] == '*' && line[i+2] == ']') {
            temp.push_back(Alive);
          }
        }
      }
      empty.push_back(temp);
  }

	infile.close();
  GridT grid(empty);
  return grid;

}

void show(GridT grid) {
  int n = BOARDLENGTH;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
       if (grid.checkCell(i, j) == Alive) {
         std::cout << "[*]";
       }
       else if (grid.checkCell(i, j) == Dead) {
         std::cout << "[ ]";
       }
     }
     std::cout << std::endl;
  }
}

void write(GridT grid) {
  ofstream outfile("data/writegrid.txt");
  int n = BOARDLENGTH;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
       if (grid.checkCell(i, j) == Alive) {
         outfile << "[*]";
       }
       else if (grid.checkCell(i, j) == Dead) {
         outfile << "[ ]";
       }
     }
     outfile << std::endl;
  }
  outfile.close();
}
