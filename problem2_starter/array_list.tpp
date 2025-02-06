#include "array_list.hpp"

template <typename T>
ArrayList<T>::ArrayList()
{
  size=0; //size of 0
  maxcap=10; //max capacity of 10 
  array= new T[maxcap]; //allocating dynamic array of max cap

}

template <typename T>
ArrayList<T>::~ArrayList()
{
  
  clear(); //clearing list by =0
  delete [] array; //deallocation of array
}

template <typename T>
ArrayList<T>::ArrayList(const ArrayList &rhs)
{
  
  size=rhs.size; //copy size
  maxcap=rhs.maxcap; //copy maxcap
  array=new T[maxcap]; //allocate new array w same capacity

  //loop to copy the elements of arrays
  for (size_t i=0;i<rhs.size;i++){
    array[i]=rhs.array[i];
  }
}

template <typename T>
ArrayList<T> &ArrayList<T>::operator=(ArrayList rhs)
{
  
  swap(rhs); //swap function
  return *this; //allows assignment chaining
}

template <typename T>
void ArrayList<T>::swap(ArrayList &rhs)
{
  // TODO, swap helper function for copy assignment
  std::swap(size,rhs.size); //swap size values
  std::swap(maxcap,rhs.maxcap); //swap max capacity
  std::swap(array,rhs.array); //swap array pointers


}

template <typename T>
bool ArrayList<T>::isEmpty() const noexcept
{
  
  return size==0; //returns true if the size is 0
}

template <typename T>
std::size_t ArrayList<T>::getLength() const noexcept
{
  
  return size; //returns the current size
}

template <typename T>
bool ArrayList<T>::insert(std::size_t position, const T &item)
{
  // TODO
  //checking the bounds for position
  if (position <1 || position> size+1){
    return false;//invalid position

  }
  if(size==maxcap){
    size_t NewCap=maxcap *2; //doubles the capacity
    T* newArray =new T[NewCap]; //allocating the new larger aray

  //copying the array
    for (size_t i=0; i<size;i++){
      newArray[i]=array[i];
    }

    delete [] array;//deallocating the old array
    array=newArray;//updating the pointer to new array
    maxcap=NewCap;//updating the max capacity

  }

  //shifting the elements to make space for new item
  for (size_t i=size;i>=position;--i){
    array[i]=array[i-1];

  }

  array[position-1] = item;//insertion of new item into position

  size++; //incrementing the size

  return true; //successful incrementation and insertion
}

template <typename T>
bool ArrayList<T>::remove(std::size_t position)
{
  //checking the bounds
  if(position < 1 || position > size+1){
    return false;
  }
  
    //shifting the elements to fill the removed psot
  for(int i = position; i<size; i++){
    array[i] = array[i+1];
  }
  size--;//decreasing size
  return true;//success
}

template <typename T>
void ArrayList<T>::clear()
{
  size=0;//reset size to 0
}

template <typename T>
T ArrayList<T>::getEntry(std::size_t position) const
{
  //checking the bounds
  if (position <1 || position>size){
    //throwing the exception
    throw std::out_of_range("Position out of range");
    

  }

  //reutrns the element at given position
  return array[position-1];


}

template <typename T>
void ArrayList<T>::setEntry(std::size_t position, const T &newValue)
{
  //checking bounds
  if (position < 1 || position> size){
    //thorwing the exception
    throw std::out_of_range("Position out of range");
  }
  array[position-1]=newValue;
  //updates the value at position
}
