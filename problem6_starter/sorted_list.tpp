#include "sorted_list.hpp"

template <typename T, typename L>
SortedList<T, L>::SortedList()
{
  // nothing to do, plist gets created on the stack
}

template <typename T, typename L>
SortedList<T, L>::SortedList(const SortedList<T, L> &x)
{
  plist = x.plist; // use plist copy assignment
}

template <typename T, typename L>
SortedList<T, L> &SortedList<T, L>::operator=(SortedList<T, L> x)
{
  plist = x.plist; // use plist copy assignment
  return *this;
}

template <typename T, typename L>
SortedList<T, L>::~SortedList()
{
  // plist destructor gets called automatically
}

template <typename T, typename L>
bool SortedList<T, L>::isEmpty() const noexcept
{
  return plist.isEmpty();
}

template <typename T, typename L>
std::size_t SortedList<T, L>::getLength() const noexcept
{
  return plist.getLength();
}

template <typename T, typename L>
void SortedList<T, L>::insert(const T &item)
{
  // TODO
  //starting at the first position (1 based in)
  std::size_t position = 1;
  //finding the correct position by comparison
  while(position<=plist.getLength()&&plist.getEntry(position)<item) {
    ++position;
  }
  //inserting item at correct position
  plist.insert(position,item);

}

template <typename T, typename L>
void SortedList<T, L>::remove(const T &item)
{
  // TODO
  //starting at first pos
  std::size_t position=1;
  while(position<=plist.getLength()) {
    if(plist.getEntry(position)==item) {
    
      plist.remove(position);
      return; // Item found and removed, exit the function
    }
    //increment to continue to traverse through list
    ++position;
  }
  //error if item not found in list
  throw std::invalid_argument("item not found in the list");
}

template <typename T, typename L>
void SortedList<T, L>::removeAt(std::size_t position)
{
  plist.remove(position);
}

template <typename T, typename L>
void SortedList<T, L>::clear()
{
  plist.clear();
}

template <typename T, typename L>
T SortedList<T, L>::getEntry(std::size_t position) const
{
  return plist.getEntry(position);
}

template <typename T, typename L>
std::size_t SortedList<T, L>::getPosition(const T &newValue)
{
  // TODO
  //start at first position in list
  std::size_t position=1;
  while(position<=plist.getLength()) {
    if(plist.getEntry(position)==newValue) {
      return position;//return position if item is found
    }
    //increment to continue to traverse through list
    ++position;
  }
  //error if the item is not found.
  throw std::invalid_argument("item not found in the list");
}