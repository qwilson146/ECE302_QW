#include "array_list.hpp"

template <typename T>
ArrayList<T>::ArrayList()
{
  size=0;
  maxcap=10;
  array= ptr<T[]>(new T[maxcap]);

}

template <typename T>
ArrayList<T>::~ArrayList()
{
  // TODO, destructor
}

template <typename T>
ArrayList<T>::ArrayList(const ArrayList &rhs)
{
  
  size=rhs.size;
  maxcap=rhs.maxcap;
  array=ptr<T[]>(new T[maxcap]);

  for (size_t i=0;i<rhs.size;i++){
    array[i]=rhs.array[i];
  }
}

template <typename T>
ArrayList<T> &ArrayList<T>::operator=(ArrayList rhs)
{
  
  size = rhs.size;
  maxcap = rhs.maxcap;
  array = ptr<T[]>(new T[maxcap]);

  for(size_t i=0;i<rhs.size;i++){
    array[i]=rhs.size[i];
  }
  return *this;
}

template <typename T>
void ArrayList<T>::swap(ArrayList &rhs)
{
  // TODO, swap helper function for copy assignment



}

template <typename T>
bool ArrayList<T>::isEmpty() const noexcept
{
  
  return size==0;
}

template <typename T>
std::size_t ArrayList<T>::getLength() const noexcept
{
  
  return size;
}

template <typename T>
bool ArrayList<T>::insert(std::size_t position, const T &item)
{
  // TODO



  return false;
}

template <typename T>
bool ArrayList<T>::remove(std::size_t position)
{
  if(position < 0 || position >= size)
    return false;
  
  size--;
  for(int i = position; i<size; i++){
    array[i] = array[i+1];
  }

  return true;
}

template <typename T>
void ArrayList<T>::clear()
{
  size=0;
}

template <typename T>
T ArrayList<T>::getEntry(std::size_t position) const
{
  if (position <0 || position>=size){
    return T();
    return array[position];

  }


}

template <typename T>
void ArrayList<T>::setEntry(std::size_t position, const T &newValue)
{
  if (position < 0 || position>= size){
    array[position]=newValue;
  }
}
