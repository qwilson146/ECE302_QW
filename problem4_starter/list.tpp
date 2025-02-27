#include "list.hpp"


//used all of my problem 2 code
//had to make minor changes in get, set, move entry functions with
//std::move function when dealing with the data [i] and data[i-x]


template <typename T>
List<T>::List()
{
  // TODO, 1-index based list, feel free to reuse your Problem 2 code
  numentries=0;
  maxcap=10;
  data=new T [maxcap];

}

template <typename T>
List<T>::~List()
{
  // TODO, 1-index based list, feel free to reuse your Problem 2 code
  clear();
  delete[] data;
}

template <typename T>
List<T>::List(const List<T> &x)
{
  // TODO, 1-index based list, feel free to reuse your Problem 2 code
  numentries=x.numentries;
  maxcap=x.maxcap;
  data = new T[maxcap];
  for(std::size_t i=0;i<numentries;i++){
    data[i]=x.data[i];

  }
}

template <typename T>
List<T> &List<T>::operator=(List<T> x)
{
  
  // TODO, 1-index based list, feel free to reuse your Problem 2 code
  swap(x);
  return *this;
}

template <typename T>
void List<T>::swap(List &x)
{
  // TODO, 1-index based list, feel free to reuse your Problem 2 code
  std::swap(numentries,x.numentries);
  std::swap(maxcap,x.maxcap);
  std::swap(data,x.data);

}

template <typename T>
bool List<T>::isEmpty() const noexcept
{
  // TODO, 1-index based list, feel free to reuse your Problem 2 code
  return numentries==0;
}

template <typename T>
std::size_t List<T>::getLength() const noexcept
{
  // TODO, 1-index based list, feel free to reuse your Problem 2 code
  return numentries;
}

template <typename T>
bool List<T>::insert(std::size_t position, const T &item)
{
  // TODO, 1-index based list, feel free to reuse your Problem 2 code
  if (position < 1 || position > numentries + 1)
    return false;


  if (numentries == maxcap)
  {
    int newcap = maxcap * 2;
    T* newData = new T[newcap];
    for (std::size_t i = 0; i < numentries; i++)
    {
      //evan fletcher helped me debug with this std::move function that I previously did not have
      //in problem 2. This just ensures transfer of data without copy assignment

        newData[i] = std::move(data[i]);
    }
    delete[] data;
    data = newData;
    maxcap=newcap;
    
  }
  for (std::size_t i = numentries; i >= position; --i)
  { 
    //different way than doing copy assignment
    data[i] = std::move(data[i-1]);
  }
  data[position - 1] = item;
  numentries++;
  return true;
}

template <typename T>
bool List<T>::remove(std::size_t position)
{
  // TODO, 1-index based list, feel free to reuse your Problem 2 code
  if (position < 1 || position > numentries){
        return false;
  }
  for (std::size_t i = position; i < numentries; i++)
    {
      //different way than doing copy assignment
        data[i-1] = std::move(data[i]);
    }
    numentries--;
    return true;
}

template <typename T>
void List<T>::clear()
{
  // TODO, 1-index based list, feel free to reuse your Problem 2 code
  numentries=0;
}

template <typename T>
T List<T>::getEntry(std::size_t position) const
{
  // TODO, 1-index based list, feel free to reuse your Problem 2 code
  if (position < 1 || position > numentries){
    throw std::out_of_range("Position out of range 1");
  }
  return data[position - 1];
}

template <typename T>
void List<T>::setEntry(std::size_t position, const T &newValue)
{
  // TODO, 1-index based list, feel free to reuse your Problem 2 code
  if (position < 1 || position > numentries){
    throw std::out_of_range("Position out of range 2");
  }
  data[position - 1] = newValue;
}

template <typename T>
void List<T>::moveEntry(std::size_t from, std::size_t to)
{
  // TODO, 1-index based list, feel free to reuse your Problem 2 code
  //slightly different than prob 2 code. 
  //makes sure the positions are within the bounds
  if (from <1 ||  from > numentries || to < 1 || to > numentries)
        throw std::out_of_range("Invalid position");
    
    //if source and destination are same we will not need to move anythign

    if (from == to) {
          return;
        }

        //storing item at position 'from' before shifting it
        T movedItem = data[from - 1];
        //moving the element forward
    if(from<to){
      //shifting to fill in spot left by moved element
      for (int i =from ; i<to ;++i){
        data[i-1]=data[i];
      }
    }
    //moving element backward
     else {
      //shift elements to make space for the moving element
        for (int i = from; i > to; --i) {
            data[i - 1] = data[i - 2];
        }
    }

    //storing item in new position
    data[to - 1] = movedItem;
}
