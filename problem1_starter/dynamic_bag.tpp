#include "dynamic_bag.hpp"

template <typename T>
DynamicBag<T>::DynamicBag()
{
  //initializing the bag w 0 elements within it
  bagsz=0;
  pointeritem = new T[bagsz]; //allocating an empty array.

}

template <typename T>
DynamicBag<T>::DynamicBag(const DynamicBag<T> &x)
{
  //copy constructor 
  bagsz=x.bagsz;
  pointeritem= new T[bagsz];//allocate mem
  for(size_t i=0; i<bagsz;i++){
    pointeritem[i]=x.pointeritem[i]; //copying item into another array

  }
}

template <typename T>
DynamicBag<T>::~DynamicBag()
//destructor
{
  //deletes the memory
  delete [] pointeritem;

}

template <typename T>
DynamicBag<T> &DynamicBag<T>::operator=(DynamicBag<T> x)
{
  //used the required copy swap idiom 
  swap(x);
  return *this;
}

template <typename T>
void DynamicBag<T>::swap(DynamicBag<T> &x)
{
  //swaps the size and items from the bags
  std::swap(pointeritem,x.pointeritem);
  std::swap(bagsz,x.bagsz);
}

template <typename T>
bool DynamicBag<T>::add(const T &item)
{
  //adds a new item into the bag
T *newPointer = new T[bagsz + 1]; //adds one more space into the array
    for (std::size_t i = 0; i < bagsz; i++)
    {
        newPointer[i] = pointeritem[i];//copys items into new array
    }
    newPointer[bagsz] = item;//add new item in array
    delete[] pointeritem; //deletes old array
    pointeritem = newPointer; //pointer for new array
    bagsz++; //size of bag is incremented.

  
}

template <typename T>
bool DynamicBag<T>::remove(const T &item)
{
  //removes item from bag
  for(std::size_t i=0;i<bagsz;i++){
    if(pointeritem[i]==item){
      //shifts the other items in the bag into their new spots in array (1 pos)
      for(std::size_t j=i;j<bagsz-1;j++){
        pointeritem[j]=pointeritem[j+1];

      }
      bagsz--;//decreases the bag size 
      return true;
    }
  }
  return false;//no item was found to remove
}

template <typename T>
bool DynamicBag<T>::isEmpty() const
{
  //simply checks if the bag is empty (would be 0 if nothing is init)
  return bagsz==0;

}

template <typename T>
std::size_t DynamicBag<T>::getCurrentSize() const
{
  
  //returns number of elements in the bag
  return bagsz;;
}

template <typename T>
bool DynamicBag<T>::contains(const T &item) const
{
    //checks if item/ element in contained in thje bag
  for (std::size_t i=0; i<bagsz;i++){
    if (pointeritem[i]==item){
      return true;//found item
    }

  }
  return false;//did not find item
}

template <typename T>
void DynamicBag<T>::clear()
{
  
  delete[] pointeritem;//deletes content in bag
  pointeritem=nullptr;//there to avoid the danglin pointer
  bagsz=0;//reset the size of bag to 0

}

template <typename T>
std::size_t DynamicBag<T>::getFrequencyOf(const T &item) const
{
  //count is there to count the occurances of a certain value in bag
  std::size_t count =0;
  for(std::size_t i=0; i<bagsz;i++){
    if (pointeritem [i] == item){
      count++;//will increment the count by 1 for each time a repeating val is found

    }
  }
  return count;//returns that count
};

template <typename T>
bool DynamicBag<T>::operator==(const AbstractBag<T> &other) const
{
  //checks to see if bags are equal both in size and content of items ie 1=1 1!=2
  if (bagsz != other.getCurrentSize()){
    return false;//returns false if size is different

  }

  for (std::size_t i=0; i<bagsz;i++){
    if (getFrequencyOf(pointeritem[i])!= other.getFrequencyOf(pointeritem[i])){
      return false;//return false if items are not the same
    }
  }
  return true;// return true if the bags are EXACT in val and size
}