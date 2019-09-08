/**
 * \file Stack.h
 * \brief Header file defining the generic Stack ADT
 * \author Mahnoor Tariq, MacID: tariqm9
 * \date March 19th, 2019
*
*/

#ifndef A3_STACK_H_
#define A3_STACK_H_

#include <vector>

/**
* \brief General stack ADT used to implmenent a stack of cards (CardStackT)
* \details This abstract data type is used to construct a default stack that will be used to construct
* any stack of cards in the game. The ADT allowed for Items to be pushed onto the stack, popped off, access the top element,
* get the size and return a sequence of Items.
*/
template <typename Item>
class Stack {
private:

  std::vector<Item> stack;

public:

  Stack();
  /**
  * \brief Creates a new Stack
  * \details Initializes a new stack given a vector of Items
  * \param stack A vector of Items
  */
  Stack(std::vector<Item> stack);
  /**
  * \brief Pushes a new item onto the Stack
  * \param An item of type Item
  * \return A new stack with the pushed item added
  */
  Stack push(Item item);
  /**
  * \brief Removes the top element of a Stack
  * \return A new array with the top element removed
  */
  Stack pop();
  /**
  * \brief Accesses the top element of an array
  * \return The top element of the stack
  */
  Item top();
  /**
  * \brief Gets the number of items in a Stack
  * \return An int of the size of the stack
  */
  unsigned int size();
  /**
  * \brief Converts the stack into a sequence of type Item
  * \return A vector of type Items in the stack
  */
  std::vector<Item> toSeq();
};


#endif
