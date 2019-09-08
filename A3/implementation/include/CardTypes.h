/**
 * \file CardTypes.h
 * \author Mahnoor Tariq
 * \brief Defines the card types used throughout the module, inclusing card suits, rank and gameboard categories.
 * \date March 20th, 2019
 */
#ifndef A3_CARD_TYPES_H_
#define A3_CARD_TYPES_H_

/**
 * \brief Describes the rank of a card.
 */
typedef unsigned short int RankT;

/**
 * \brief RankT for an Ace.
 */
#define ACE    1

/**
 * \brief RankT for an Jack.
 */
#define JACK   11

/**
 * \brief RankT for a Queen.
 */
#define QUEEN  12

/**
 * \brief RankT for a King.
 */
#define KING   13

enum SuitT {Heart, Diamond, Club, Spade};
enum CategoryT {Tableau, Foundation, Deck, Waste};

struct CardT {
  SuitT s;
  RankT r;
};

#endif
