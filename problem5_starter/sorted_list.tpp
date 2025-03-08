#include "sorted_list.hpp"
#include <stdexcept>

template <typename T>
SortedList<T>::SortedList() : List<T>() // base called, completed
{
}

template <typename T>
SortedList<T>::SortedList(List<T> unsorted_list)
{
  // TODO

//gets the length
  std::size_t length = unsorted_list.getLength();
  //loop through elements and insert into sorted list
  for (std::size_t i=1; i< length; ++i) {
    insert(unsorted_list.getEntry(i));
  }
}

template <typename T>
SortedList<T>::SortedList(const SortedList<T> &x) : List<T>(x) // base called, completed
{
}

template <typename T>
SortedList<T> &SortedList<T>::operator=(SortedList<T> x)
{
  List<T>::operator=(x);
  return *this;
} // base called, completed

template <typename T>
SortedList<T>::~SortedList()
{
  // base destructor gets called automatically
}

template <typename T>
bool SortedList<T>::isEmpty() const noexcept
{
  return List<T>::isEmpty();
} // base called, completed

template <typename T>
std::size_t SortedList<T>::getLength() const noexcept
{
  return List<T>::getLength();
} // base called, completed

template <typename T>
void SortedList<T>::insert(const T &item)
{
  // TODO, check description in the header file sorted_list.hpp

  //get the length
  std::size_t length = getLength();
  //if length is 0 (empty) it will insert at the first pos
  if (length == 0) 
  {
    List<T>::insert(1, item); 
  }
  else
  {
    //1 based indexing kept in mind
    //will find th ecorect position for insertion
    std::size_t i = 1;
    while (i <= length && List<T>::getEntry(i) < item)
    {
      ++i;
    }
    //inserts the item in sorted correct positon
    List<T>::insert(i, item); 
  }
}

template <typename T>
void SortedList<T>::remove(const T &item)
{
  // TODO, check description in the header file sorted_list.hpp
  //gets position of item
  std::size_t pos = getPosition(item);
  //remove item at that position
  List<T>::remove(pos);
}

template <typename T>
void SortedList<T>::removeAt(std::size_t position)
{
  // TODO, check description in the header file sorted_list.hpp
  //calls the base remove function
  List<T>::remove(position);
}

template <typename T>
void SortedList<T>::clear()
{
  List<T>::clear();
} // base called, completed

template <typename T>
T SortedList<T>::getEntry(std::size_t position) const
{
  return List<T>::getEntry(position);
} // base called, completed

template <typename T>
std::size_t SortedList<T>::getPosition(const T &item)
{
  // TODO, check description in the header file sorted_list.hpp
  //gets the current length
  std::size_t length = getLength();
  //looping through the list
  for (std::size_t i = 1; i <= length; ++i)
  {
    //checks if the item matches
    if (List<T>::getEntry(i) == item)
    {
      //returns the position
      return i;
    }
  }
  //throws this error if tht item is not found
  throw std::invalid_argument("Item not found"); 
}