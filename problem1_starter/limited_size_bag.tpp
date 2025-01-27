#include "limited_size_bag.hpp"

template <typename T>
LimitedSizeBag<T>::LimitedSizeBag()
{
  //initialize bag to 0
  CurrentSize=0;

}

template <typename T>
bool LimitedSizeBag<T>::add(const T &item)
{
  // TODO
  //adds item to bag as long as max size is not exceeded
  if(CurrentSize<maxsize){
    items[CurrentSize++]=item;
    return true;
  }
  return false;//bag is already full
}

template <typename T>
bool LimitedSizeBag<T>::remove(const T &item)
{
  //removes a specified item if it is found in the bag
  for (std::size_t i=0;i<CurrentSize;i++){
    if(items[i]==item){
      items[i]=items[CurrentSize-1];
      --CurrentSize;//de increment the size
      return true;
    }
  }  
  return false;//no item was found 
}

template <typename T>
bool LimitedSizeBag<T>::isEmpty() const
{
  //returns the size of 0 if the bag is empty
  return CurrentSize==0;
  
}

template <typename T>
std::size_t LimitedSizeBag<T>::getCurrentSize() const
{
  //returns the current size of the bag at that moment in time
  return CurrentSize;
}

template <typename T>
bool LimitedSizeBag<T>::contains(const T &item) const
{
  // TODO
  //will return true if that specific item is found within the bag
  for(std::size_t i=0;i<CurrentSize;i++){
    if(items[i]==item){
      return true;
    }
  }
  return false;//reutn false if not found
}

template <typename T>
void LimitedSizeBag<T>::clear()
{
  //clears the bag by setting the size to 0 so nothing can be contained within
  CurrentSize=0;
}

template <typename T>
std::size_t LimitedSizeBag<T>::getFrequencyOf(const T &item) const
{
  //counts the number of times that value is found within the bag
  std::size_t count=0;
  for(std::size_t i=0; i<CurrentSize;i++){
    if (items[i]==item){
      ++count;//will increment by 1 for each time found
    }
  }
  return count;//returns the final count of occurances
};

template <typename T>
bool LimitedSizeBag<T>::operator==(const AbstractBag<T> &other) const
{
  //compares bags for equality both in size and value will return false if either one fails
  if(getCurrentSize() != other.getCurrentSize()){
    return false;

  }

  for(std::size_t i=0; i<CurrentSize;i++){
    if(getFrequencyOf(items[i])!=other.getFrequencyOf(items[i])){
      return false;
    }
  }
  return true;//will return true if both the size and vals (vals and their occurances) are
  //the same in each seperate bag.
}