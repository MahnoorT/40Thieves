/**
 * \file Stack
 * \brief Implementation of the Stack ADT with behaviours defined.
 * \author Mahnoor Tariq, MacID: tariqm9
 * \date March 20th, 2019
*
*/

// Implementation here
#include "CardTypes.h"
#include "Stack.h"
#include "CardStack.h"
#include <stdexcept>


template <class T>
Stack<T>::Stack() {
  this->stack = {};
};

template <class T>
Stack<T>::Stack(std::vector<T> stack) {
  this->stack = stack;
};

template <class T>
Stack<T> Stack<T>::push(T card) {
  this->stack.push_back(card);
  return Stack(this->stack);
};

template <class T>
Stack<T> Stack<T>::pop() {
  if(this->stack.size() == 0) {
    throw std::out_of_range("Stack is empty.");
  }
  this->stack.pop_back();
  return Stack(this->stack);
};

template <class T>
T Stack<T>::top() {
  if(this->stack.size() == 0) {
    throw std::out_of_range("Stack is empty.");
  }
  return (this->stack.back());
};

template <class T>
unsigned int Stack<T>::size() {
  return (this->stack.size());
};

template <class T>
std::vector<T> Stack<T>::toSeq() {
  return (this->stack);
};

// Keep this at bottom
template class Stack<CardT>;
