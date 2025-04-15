#include <cmath> // for log2
#include "ArrayMaxHeap.hpp"
#include <stdexcept>

template <typename ItemType>
int ArrayMaxHeap<ItemType>::getLeftChildIndex(const int nodeIndex) const
{
   return (2 * nodeIndex) + 1;
} // end getLeftChildIndex, private method

template <typename ItemType>
int ArrayMaxHeap<ItemType>::getRightChildIndex(const int nodeIndex) const
{
   return (2 * nodeIndex) + 2;
} // end getRightChildIndex, private method

template <typename ItemType>
int ArrayMaxHeap<ItemType>::getParentIndex(const int nodeIndex) const
{
   return (nodeIndex - 1) / 2;
} // end getParentIndex, private method

template <typename ItemType>
bool ArrayMaxHeap<ItemType>::isLeaf(const int nodeIndex) const
{
   return (getLeftChildIndex(nodeIndex) >= itemCount);
} // end isLeaf, private method

template <typename ItemType>
void ArrayMaxHeap<ItemType>::heapRebuild(const int subTreeNodeIndex)
{
   if (!isLeaf(subTreeNodeIndex))
   {
      // TODO

      // Find larger child
      // Swap with larger child if node value is smaller
      // Continue with the recursion at that child

      int leftkid=getLeftChildIndex(subTreeNodeIndex);//getting index of left
      int rightkid=getRightChildIndex(subTreeNodeIndex);//getting index of right
      int largechild=leftkid;//assuming the left kid is larger

      //if right exist and larger update the large child var
      if(rightkid<itemCount && items[rightkid]>items[leftkid]){
         largechild=rightkid;
      }
      //if child is larger than par swap and do recursion
      if(items[subTreeNodeIndex]<items[largechild]){
         std::swap(items[subTreeNodeIndex],items[largechild]);
         heapRebuild(largechild);
      }

   } // end if
} // end heapRebuild, private method

template <typename ItemType>
void ArrayMaxHeap<ItemType>::heapCreate()
{
   // Start with the last parent node and rebuild the heap to the root
   for (int index = itemCount / 2 - 1; index >= 0; index--)
   {
      heapRebuild(index);
   } // end for
} // end heapCreate, private method

//******************************************************************
//
// Public methods start here
//
//******************************************************************

template <typename ItemType>
ArrayMaxHeap<ItemType>::ArrayMaxHeap() : itemCount(0)
{
} // end default constructor

template <typename ItemType>
ArrayMaxHeap<ItemType>::ArrayMaxHeap(const ItemType someArray[], const int arraySize) : itemCount(arraySize)
{
   // Copy given values into the array
   for (int i = 0; i < itemCount; i++)
      items[i] = someArray[i];

   // Reorganize the array into a heap
   heapCreate();
} // end constructor

template <typename ItemType>
ArrayMaxHeap<ItemType>::~ArrayMaxHeap()
{
   clear();
} // end destructor

template <typename ItemType>
bool ArrayMaxHeap<ItemType>::isEmpty() const noexcept
{
   return itemCount == 0;
} // end isEmpty

template <typename ItemType>
int ArrayMaxHeap<ItemType>::getHeight() const noexcept
{
   return ceil(log2(itemCount + 1));
} // end getHeight

template <typename ItemType>
int ArrayMaxHeap<ItemType>::getNumberOfNodes() const noexcept
{
   return itemCount;
} // end getNumberOfNodes

template <typename ItemType>
void ArrayMaxHeap<ItemType>::clear() noexcept
{
   itemCount = 0;
} // end clear

template <typename ItemType>
ItemType ArrayMaxHeap<ItemType>::peekTop() const
{
   // TODO
   //checking the bounds
   if(isEmpty()){
      throw std::out_of_range("empty heap");

   } 
   //root holds max
   return items[0];// Placeholder
} // end peekTop

template <typename ItemType>
bool ArrayMaxHeap<ItemType>::add(const ItemType &newData)
{
   // TODO

   // Place newData in the last position
   // Swap it with its parent until the heap property is restored
   // Make sure to update itemCount

   //checking if heap is full (took numerous tries to realize it was ==)
   if(itemCount==DEFAULT_CAPACITY){
   return false;
   }

   //check for dups (got this from gradescope)
   for (int i=0;i<itemCount;i++){
      if(items[i]==newData){
         return false;
      }
   }
   
   //inserting an item at the last index
   int nIndex=itemCount;
   items[nIndex]=newData;
   //updating the item count
   itemCount++;

   //maintaining the heap
   int partentind=getParentIndex(nIndex);
   while(nIndex>0 && items[nIndex]>items[partentind]){
      std::swap(items[nIndex],items[partentind]);
      nIndex=partentind;
      partentind= getParentIndex(nIndex);
   }

   return true;
   // Placeholder
} // end add

template <typename ItemType>
bool ArrayMaxHeap<ItemType>::remove()
{
   // TODO

   // remove the last item
   // swap it with the root
   // rebuild the heap
   // make sure to update itemCount
   if(isEmpty()){
      return false;
      //return false bc you cant remove from an empty heap

   }
   //replacing the root with the last element
   items[0]=items[itemCount-1];
   itemCount--;//updating the count
   heapRebuild(0);
   return true; // Placeholder
} // end remove

template <typename ItemType>
void ArrayMaxHeap<ItemType>::heapSort(ItemType anArray[], int n)
{
   // TODO

   // Build initial heap
   // Remove root, swap, and rebuild the heap

   //comparing to the capacity of the heap
   if(n>DEFAULT_CAPACITY){
      throw std::invalid_argument("array exceed cap of heap");

   }

   //checking for dups again
   for (int i=0;i<n;i++){

      for (int j=i+1;j<n;j++){
         if (anArray[i]==anArray[j])
         {
            throw std::invalid_argument("duplicates present");
         }
         
      }
   }

   //realized you need to reset the heap before sorting
   //loading elements into the heap
   clear();
   for (int i=0;i<n;i++){
      add(anArray[i]);//inserting into the heap
   }

   //sorting descending
   for(int i=0;i<n;i++){
      anArray[i]=peekTop();//max val
      remove();//removing from heap
   }

} // end heapSort
