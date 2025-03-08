#include "list.hpp"

template <typename T>
List<T>::List()
{
  // TODO, refer to Problem 2 or 4
  //initializing all variables
  data=nullptr;
  size=0;
  cap=0;

}

template <typename T>
List<T>::~List()
{
  // TODO, refer to Problem 2 or 4
  //deallocating mem
  delete [] data;

}

template <typename T>
List<T>::List(const List<T> &x)
{
  // TODO, refer to Problem 2 or 4
  //deep copy for provided X with size and cap
  //new array of size capacity is allocated for each data element
  size=x.size;
  cap=x.cap;
  data=new T[cap];
  //for loop to copy all data over
  for(std::size_t i=0;i<size;i++){
    data[i]=x.data[i];
  }
}

template <typename T>
List<T> &List<T>::operator=(List<T> x)
{
  // TODO, refer to Problem 2 or 4
  //swap function is called
  swap(x);

  return *this;
}

template <typename T>
void List<T>::swap(List &x)
{
  // TODO, refer to Problem 2 or 4
  //willswap variables into x list and then into a tempearay var
  T* tempdata=data;
  std::size_t tempsize=size;
  std::size_t tempcap=cap;
  data=x.data;
  size=x.size;
  cap=x.cap;
  x.data=tempdata;
  x.size=tempsize;
  x.cap=tempcap;

}

template <typename T>
bool List<T>::isEmpty() const noexcept
{
  // TODO, refer to Problem 2 or 4
  //if true if size is 0 the list must be empty
  return size==0;
}

template <typename T>
std::size_t List<T>::getLength() const noexcept
{
  // TODO, refer to Problem 2 or 4
  //returns the size of the list
  return size;
}

template <typename T>
void List<T>::insert(std::size_t position, const T &item)
{
  // TODO, implement the insert function using 1-based indexing
  // Note the void return type and throw std::out_of_range if the position is invalid
  //throw invalid pos if pos is out of bounds
  
  if (position < 1 || position > size + 1) {
    throw std::out_of_range("Invalid position");
  }
//if size and cap are equal (list is full) cap is doubled
  if (size == cap) { 
    cap = cap == 0 ? 1 : cap * 2;
    T* newData = new T[cap];//allocate new array
    //loop to copy data  over
    for (std::size_t i = 0; i < size; ++i) {
      newData[i] = data[i]; 
    }
    delete[] data;//free the old array
    data = newData;
  }
  //shifting elements to the right
  for (std::size_t i = size; i >= position; --i) {
    data[i] = data[i - 1]; 
  }
  
  //inseting the item at the given position keeping in mind the 1 based index

  data[position - 1] = item; 
  ++size; //incrementing the size
}

template <typename T>
void List<T>::remove(std::size_t position)
{
  // TODO, implement the remove function using 1-based indexing
  // Note the void return type and throw std::out_of_range if the position is invalid
  if (position < 1 || position > size) { 
    throw std::out_of_range("Invalid position");
  }

  //shifting elements to the left to remove
  for (std::size_t i = position - 1; i < size - 1; ++i) {
    data[i] = data[i + 1];
  }
  //decrement the size
  --size;
}

template <typename T>
void List<T>::clear()
{
  // TODO, refer to Problem 2 or 4
  //compleelt clearin thelist
  delete [] data;
  data=nullptr;
  size=0;
  cap=0;

}

template <typename T>
T List<T>::getEntry(std::size_t position) const
{
  // TODO, refer to Problem 2 or 4
  // Throws std::out_of_range if the position is invalid
  if (position < 1 || position > size) {
    throw std::out_of_range("Invalid position");
  }
//item at the 0 base index (-1)
  return data[position - 1];
}

template <typename T>
void List<T>::setEntry(std::size_t position, const T &newValue)
{
  // TODO, refer to Problem 2 or 4
  // Throws std::out_of_range if the position is invalid
  if (position < 1 || position > size) { 
    throw std::out_of_range("Invalid position");
  }
  //setting new val at index pos -1
  data[position - 1] = newValue;
}