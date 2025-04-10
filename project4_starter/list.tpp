#include "list.hpp"
//list TPP was brought in from problem 6 same file 

template <typename T>
List<T>::List()
{
  data=nullptr;
  size=0;
  capacity=0;
}

template <typename T>
List<T>::~List()
{
  delete [] data;
}

template <typename T>
List<T>::List(const List<T> &x)
{
    //initialized to nullptr
    data=nullptr;
    //setting 0 as it will hace stuff copied in
    size=0;
    //same as size
    capacity=0;
    //copy assignment
    *this = x;
}

template <typename T>
List<T> &List<T>::operator=(List<T> x)
{
  swap(x);
  return *this;
}

template <typename T>
void List<T>::swap(List &x)
{
  std::swap(data, x.data);
  std::swap(size, x.size);
  std::swap(capacity, x.capacity);
}

template <typename T>
bool List<T>::isEmpty() const noexcept
{
  //return true if 0 (empty)
  return size==0;

}

template <typename T>
std::size_t List<T>::getLength() const noexcept
{
  //size is length in this case
  return size;
}

template <typename T>
void List<T>::insert(std::size_t position, const T &item)
{
    //checking if the position is valid
    if (position<1||position>size+1){
      throw std::out_of_range("Position is out of range");
    }
  
    //if list is full we need to resize it 
    if(size==capacity) 
    {
      //doubling the capacity 
      T* new_data=new T[capacity==0?1:capacity*2];
      for(std::size_t i=0; i<size;++i)
      {
        new_data[i]=data[i];//copying current data over
      }
      //deleting old array 
  
      delete[] data;
      //assigning new data
      data = new_data;
      //updating the capacity
      capacity=(capacity==0?1:capacity*2);
    }
  
    for(std::size_t i=size;i>=position;--i)
    {
      //shifting elements from the end of the lsit to the right
      data[i]=data[i-1];
    }
  
    //insert at correct position
    data[position-1]=item;
    //incrementing the size
    ++size;
}

template <typename T>
void List<T>::remove(std::size_t position)
{
  if(position<1||position>size){
    //check if position is valid
    throw std::out_of_range("position is out of range");
  }
  //shifting the elements to left to fill gap
  for(std::size_t i=position-1;i<size-1;++i)
  {
    data[i]=data[i+1];
  }
  //decrementing the size
  --size;
}

template <typename T>
void List<T>::clear()
{
  
    //clearing the lists
    delete[] data;
    data = nullptr;
    size = 0;
    capacity = 0;
}

template <typename T>
T List<T>::getEntry(std::size_t position) const
{
  
  if (position < 1 || position > size){
    throw std::out_of_range("position is out of range");
    }
    //returning the correct item
    return data[position-1];
}

template <typename T>
void List<T>::setEntry(std::size_t position, const T &newValue)
{
  
  //checking if position is valid
  if(position<1||position>size){
    throw std::out_of_range("position is out of range");
  }
  //updating with new entry at the correct position
  data[position-1]=newValue;
}