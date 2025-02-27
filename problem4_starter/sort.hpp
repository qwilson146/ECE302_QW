#ifndef _SORT_HPP
#define _SORT_HPP

#include "list.hpp"

/** Sorts a list into ascending order. Uses the quick sort method.
 @pre  list[first..last] is a list.
 @post  list[first..last] is sorted.
 @throw std::out_of_range if first < 1 or last > list.getLength()
 @param list  The given list.
 @param first  The start element to consider in list.
 @param last  The end element to consider in list. */

template <typename T>
void quick_sort(List<T> &list, int first, int last)
{
    // TODO, note the 1-index based list

    // must call partition below
    //ensure indices are within the bounds
    if (first < 1 || last> list.getLength()){
        //error if they arent
        throw std::out_of_range("Invalid indices");
    }
//if list contains 1 or 0 elements there is no need to sort
    if(first>=last){
        return;
    }
    //partion the list and get index of pivot
    int pivotIndex = partition(list, first, last);
    //recursive sort left sublist (before pivot)
    quick_sort(list, first, pivotIndex - 1);
    //recursive sort right siblist (after pivot)
    quick_sort(list, pivotIndex + 1, last);
    
}

/** Partitions the entries in a list about a pivot entry for quicksort.
 @pre  list[first..last] is an list; first <= last.
 @throw std::out_of_range if first > last, or if first < 1 or last > list.getLength()
 @post  list[first..last] is partitioned such that:
 S1 = list[first..pivotIndex-1] <= pivot
      list[pivotIndex]          == pivot
 S2 = list[pivotIndex+1..last]  >= pivot
 @param list  The given list.
 @param first  The start entry to consider in list.
 @param last  The end entry to consider in list.
 @return  The index of the pivot.
 */

template <typename T>
int partition(List<T> &list, int first, int last)
{

    // TODO, note the 1-index based list

    // You can choose the pivot yourself, but no matter what you choose
    // list[first..pivotIndex-1] <= pivot, list[pivotIndex] == pivot, list[pivotIndex + 1..last] >= pivot

    //checking that indices are in bounds
    if(first < 1 || last > list.getLength() || first > last){
        //error thrown if they are not
        throw std::invalid_argument("stuff be wrong bro");
    }
    //getting the last element for the pivot
    T pivot = list.getEntry(last);
    //index traces where the elements are at to where they should be places
    int index=first-1;
    for (int i = first; i < last; i++)
    {
        
        //if current elem is less or equal to pivot move it to position by swapping]
        if (list.getEntry(i) <= pivot)
        {
            //increment index
            index++;
            //move the less than element to the left
            list.moveEntry(i,index);
            
        }

        
    }
    //after partition has been done the pivot gets palced in the sortee positions
    if(index+1!= last){
    list.moveEntry(last,index+1);
}
    //returns the final position of where theindex is at.
    return index+1;
}
#endif
