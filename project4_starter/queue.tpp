#include "queue.hpp"

template <typename T, typename L>
void Queue<T, L>::enqueue(const T &item)
{
  // TODO, check hints in HW6 code analysis
  //oldest items at the back
  internal_list.insert(1,item);
}

template <typename T, typename L>
void Queue<T, L>::dequeue()
{
  // TODO, check hints in HW6 code analysis
  //removing item at the back of the lsit
  internal_list.remove(internal_list.getLength());
  
}

template <typename T, typename L>
T Queue<T, L>::peekFront()
{
  // TODO, check hints in HW6 code analysis
  //accessing the last element in the lsit
  return internal_list.getEntry(internal_list.getLength());

}

template <typename T, typename L>
bool Queue<T, L>::isEmpty() const
{
  // TODO, check hints in HW6 code analysis
  //checking if the queue is emopty and returning true or false based on it
  return internal_list.isEmpty();
}