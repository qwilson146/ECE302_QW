#include "list.hpp"
//pretty much the same set up as problem 5

template <typename T>
List<T>::List()
{
  // TODO
  data=nullptr;
  size=0;
  capacity=0;
}

template <typename T>
List<T>::~List()
{
  // TODO
  clear();
}

template <typename T>
List<T>::List(const List<T> &x)
{
  // TODO
  data=nullptr;
  size=0;
  capacity=0;
  *this = x;

}

template <typename T>
List<T> &List<T>::operator=(List<T> x)
{
  // TODO
  swap(x);
  return *this;
}

template <typename T>
void List<T>::swap(List<T> &x)
{
  // TODO
  std::swap(data, x.data);
  std::swap(size, x.size);
  std::swap(capacity, x.capacity);
}

template <typename T>
bool List<T>::isEmpty() const noexcept
{
  // TODO
  return size==0;
}

template <typename T>
std::size_t List<T>::getLength() const noexcept
{
  // TODO
  return size;
}

template <typename T>
void List<T>::insert(std::size_t position, const T &item)
{
  // TODO
  if (position<1||position>size+1){
    throw std::out_of_range("Position is out of range");
  }

  if(size==capacity) 
  {
    T* new_data=new T[capacity==0?1:capacity*2];
    for(std::size_t i=0; i<size;++i)
    {
      new_data[i]=data[i];
    }
    delete[] data;
    data = new_data;
    capacity=(capacity==0?1:capacity*2);
  }

  for(std::size_t i=size;i>=position;--i)
  {
    data[i]=data[i-1];
  }

  data[position-1]=item;
  ++size;
}

template <typename T>
void List<T>::remove(std::size_t position)
{
  // TODO
  if(position<1||position>size){
    throw std::out_of_range("position is out of range");
  }
  for(std::size_t i=position-1;i<size-1;++i)
  {
    data[i]=data[i+1];
  }

  --size;
}

template <typename T>
void List<T>::clear()
{
  // TODO
  delete[] data;
  data = nullptr;
  size = 0;
  capacity = 0;
}

template <typename T>
T List<T>::getEntry(std::size_t position) const
{
  // TODO
  if (position < 1 || position > size){
  throw std::out_of_range("position is out of range");
  }

  return data[position-1];
}

template <typename T>
void List<T>::setEntry(std::size_t position, const T &newValue)
{
  // TODO
  if(position<1||position>size){
    throw std::out_of_range("position is out of range");
  }
  data[position-1]=newValue;
}
