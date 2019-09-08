/**
 * \file Gameboard
 * \brief Implementation for the gameboard defining the gameboard including mocing cards, checking valif moves, etc.
 * \author Mahnoor Tariq, MacID: tariqm9
 * \date March 20th, 2019
*
*/
#include "Stack.h"
#include "GameBoard.h"

#include <vector>
#include <iostream>


BoardT::BoardT(std::vector<CardT> cards){

  //Checking if two cards of each type exist in the deck
  if (!two_decks(cards)) {throw std::invalid_argument("Wrong deck");}

  //Initializing the tableau
  this->tableau = BoardT::tab_deck(cards);

  //Initializing the deck
  CardStackT deck;
  for (int i = 40; i < 104; i++){
    deck = deck.push(cards[i]);
  }

  this->deck = deck;

  //Initializing waste
  CardStackT waste;
  this->waste = waste;

  this->foundation = BoardT::init_seq(8);

};

SeqCrdStckT BoardT::init_seq(unsigned int n){
  std::vector<CardStackT> seq;
  for (unsigned int i = 0; i < n; i++){
    CardStackT type;
    seq.push_back(type);
  }
  return seq;
}

bool BoardT::two_decks(std::vector<CardT> cards) {
    unsigned int counter = 0;
    if (cards.size() != 104) {return false;}
    for (RankT r = ACE; r <= KING; r++) {
      for (unsigned int s = 0; s < 4; s++) {
        CardT n = {static_cast<SuitT>(s), r};
        for (unsigned int i = 0; i < 104; i++) {
          if (cards[i].r == n.r && cards[i].s == n.s) {counter += 1;}
        }
      }
    }

    if (counter == 104) {return true;}
    return false;
}

SeqCrdStckT BoardT::tab_deck(std::vector<CardT> cards) {
  std::vector<CardStackT> Seq;
  for (int i = 0; i < 10; i++) {
    CardStackT temp;
    for (int j = 4*i; j <= 4*(i+1)-1; j++) {
      temp.push(cards[j]);
    }
    Seq.push_back(temp);
  }
  return Seq;
}


bool BoardT::is_valid_tab_mv(CategoryT c, unsigned int n1, unsigned int n2) {
  switch (c){
    case Tableau:
      if (n1 < 0 || n1 > 9 || n2 < 0 || n2 > 9) {throw std::out_of_range("Out of range");}
      break;
    case Foundation:
      if (n1 < 0 || n1 > 9 || n2 < 0 || n2 > 7) {throw std::out_of_range("Out of range");}
      break;
    case Waste:
      break;
    case Deck:
      break;
  }

  switch (c){
    case Deck:
      return false;
    case Waste:
      return false;
    case Tableau:
      if (this->tableau[n2].size() == 0) {return true;}
      if (this->tableau[n1].size() == 0) {return false;}
      if (this->tableau[n1].top().s == this->tableau[n2].top().s && this->tableau[n1].top().r == this->tableau[n2].top().r - 1) {return true;}
      return false;
    case Foundation:
      if (this->tableau[n1].size() == 0) {return false;}
      if (this->foundation[n2].size() == 0 && this->tableau[n1].top().r == ACE) {return true;}
      if (this->foundation[n2].size() == 0) {return false;}
      if (this->tableau[n1].top().s == this->foundation[n2].top().s && this->tableau[n1].top().r == this->foundation[n2].top().r + 1) {return true;}
      return false;
  }
  return false;
}

bool BoardT::is_valid_waste_mv(CategoryT c, unsigned int n) {
  switch (c) {
    case Tableau:
      if (n < 0 || n > 9) {throw std::out_of_range("Out of range");}
      break;
    case Foundation:
      if (n < 0 || n > 7) {throw std::out_of_range("Out of range");}
      break;
    case Waste:
      break;
    case Deck:
      break;
  }
  if (this->waste.size() == 0) {return false;}
  switch (c) {
    case Deck:
      return false;
    case Waste:
      return false;
    case Tableau:
      if (this->tableau[n].size() == 0) {return true;}
      if (this->waste.top().s == this->tableau[n].top().s && this->waste.top().r == this->tableau[n].top().r + 1) {return true;}
      return false;
    case Foundation:
      if (this->foundation[n].size() == 0 && this->waste.top().r == ACE) {return true;}
      if (this->foundation[n].size() == 0) {return false;}
      if (this->waste.top().s == this->foundation[n].top().s && this->waste.top().r == this->foundation[n].top().r + 1) {return true;}
      return false;
  }
  return false;
}

bool BoardT::is_valid_deck_mv() {
  if (this->deck.size() > 0) {return true;}
  return false;
}

void BoardT::tab_mv(CategoryT c, unsigned  int n1, unsigned int n2) {
    bool x = is_valid_tab_mv(c, n1, n2);
    if (x == false) {
      throw std::invalid_argument("Move not possible");
    }

    switch(c){
      case Tableau:
        this->tableau[n2] = this->tableau[n2].push(this->tableau[n1].top());
        this->tableau[n1] = this->tableau[n1].pop();
        break;
      case Foundation:
        this->foundation[n2] = this->foundation[n2].push(this->tableau[n1].top());
        this->tableau[n1] = this->tableau[n1].pop();
        break;
      case Waste:
        break;
      case Deck:
        break;
    }
}

void BoardT::waste_mv(CategoryT c, unsigned  int n) {
  bool x = is_valid_waste_mv(c, n);

  if (x == false) {
    throw std::invalid_argument("Move not possible");
  }

  switch(c){
    case Tableau:
      this->tableau[n] = this->tableau[n].push(this->waste.top());
      this->waste = this->waste.pop();
      break;
    case Waste:
      break;
    case Deck:
      break;
    case Foundation:
      this->foundation[n] = this->foundation[n].push(this->waste.top());
      this->waste = this->waste.pop();
      break;
  }
}

void BoardT::deck_mv() {
  bool x = is_valid_deck_mv();
  if (x == false) {
    throw std::invalid_argument("Move not possible");
  }

  this->waste = this->waste.push(this->deck.top());
  this->deck = this->deck.pop();

}

CardStackT BoardT::get_tab(int i) {
  if (i < 0 || i > 9) {
    throw std::bad_alloc();
  }

  return this->tableau[i];
}

CardStackT BoardT::get_foundation(int i) {
  if (i < 0 || i > 7) {
    throw std::bad_alloc();
  }

  return this->foundation[i];
}

CardStackT BoardT::get_deck() {
  return this->deck;
}

CardStackT BoardT::get_waste() {
  return this->waste;
}

bool BoardT::valid_mv_exists() {
  return valid_tab_mv() || valid_waste_mv() || is_valid_deck_mv();
}

bool BoardT::is_win_state() {
  int counter = 0;
  for (int i = 0; i < 8; i++) {
    if (this->foundation[i].size() > 0 && this->foundation[i].top().r == KING) {
      counter += 1;
    }
  }
  if (counter == 8) {
    return true;
  }
  return false;
}

bool BoardT::valid_tab_mv() {
  //Checking to see if a move exists inside a board
  CategoryT tab = Tableau;
  CategoryT f = Foundation;
  int check = 0;
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if (is_valid_tab_mv(tab, i, j) == true) {check += 1;}
    }
    for (int k = 0; k < 8; k++) {
      if (is_valid_tab_mv(f, i, k) == true) {check += 1;}
    }
  }

  if (check != 0) {return true;}
  return false;
}

bool BoardT::valid_waste_mv() {
  CategoryT tab = Tableau;
  CategoryT f = Foundation;
  int check = 0;
  for (int i = 0; i < 8; i++) {
    if (is_valid_waste_mv(tab, i) == true) {check += 1;}
    if (is_valid_waste_mv(f, i) == true) {check += 1;}
  }

  if (check != 0) {return true;}
  return false;

}
