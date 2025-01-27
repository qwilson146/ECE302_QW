#ifndef _DYNAMIC_BAG_HPP_
#define _DYNAMIC_BAG_HPP_

#include "abstract_bag.hpp"

template <typename T>
class DynamicBag : public AbstractBag<T>
{
public:
  // default constructor
  DynamicBag();

  // copy constructor
  DynamicBag(const DynamicBag &x);

  // destructor
  ~DynamicBag();

  // copy assignment
  DynamicBag &operator=(DynamicBag x);

  // swap for copy swap idiom
  void swap(DynamicBag &x);

  // add an item to the bag
  bool add(const T &item);

  // remove an item
  bool remove(const T &item);

  // check is the bag is empty
  bool isEmpty() const;

  // get number of items in the bag
  std::size_t getCurrentSize() const;

  // clear the bag contents
  void clear();

  // count how many time item occurs in bag
  std::size_t getFrequencyOf(const T &item) const;

  // check if item is in the bag
  bool contains(const T &item) const;

  // check if two bags are equal
  bool operator==(const AbstractBag<T> &other) const;

private:
  // TODO
  T* pointeritem; // pointer to dynam alloc array of item to bag
  std::size_t bagsz; //the size of the bag 
  
};

#include "dynamic_bag.tpp"

#endif
