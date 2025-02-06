#include "linked_list.hpp"

//talked with Evan Fletcher where he helped me understand errors within my code and potential issues that could arise with how I had it
//formatted and the way it was traversing through lists. 
//Also tallked to TA Elyse for help and clarification on what was required and how I would best approach the functions.

template <typename T>
LinkedList<T>::LinkedList()
{
  size=0; //setting size to 0
  first=nullptr; //setting node pointer to null (empty)

}

template <typename T>
LinkedList<T>::~LinkedList()
{
  clear(); //clearing all nodes and memory

}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T> &x)
{
  size=x.size; //copy the size
  first=nullptr; //initializing pointer to null
//checking the list if empty or not
  if(x.first){
    first = new Node<T>(x.first->getItem());//copy first node
    Node<T> *currentnow=x.first->getNext();//pointer to move through the list
    Node<T> * currentnew=first; //pointer to move across new list
    //copys all nodes while true (if it steps out will be false)
    while(currentnow){
       currentnew->setNext(new Node<T>(currentnow->getItem()));//creating new node
        currentnew = currentnew->getNext();//moving to next node
        currentnow = currentnow->getNext();//ove to next node in source
    }
  }



}

template <typename T>
LinkedList<T> &LinkedList<T>::operator=(LinkedList<T> x)
{
  //swapping the contents 
  swap(x);

  return *this;


}

template <typename T>
void LinkedList<T>::swap(LinkedList &x)
{
  std::swap(first,x.first);//swap first pointers
  std::swap(size,x.size);//swappint the sizes


}

template <typename T>
bool LinkedList<T>::isEmpty() const noexcept
{
  return size==0;//returns true if the size is 0

}

template <typename T>
std::size_t LinkedList<T>::getLength() const noexcept
{
  return size;//returns the current size 
  
}

template <typename T>
bool LinkedList<T>::insert(std::size_t position, const T &item)
{
  //checking the bounds 
   if (position < 1 || position > size + 1) {
        return false;
    }
    Node<T> *nnode = new Node<T>(item);//creating new nodes
    if (position == 1) {
        nnode->setNext(first);//setting new node to current first node
        first = nnode;//updating the pointers
    } else {
        Node<T> *pnode = first;
        //teaversing the nodes 
        for (size_t i = 1; i < position - 1; i++) {
            pnode = pnode->getNext();
        }
        //inserting new node at correct position
        nnode->setNext(pnode->getNext());
        pnode->setNext(nnode);
    }
    size++;//incrementation of the size
    return true;

}

template <typename T>
bool LinkedList<T>::remove(std::size_t position)
{
  //checking the bounds of position
if(position<1||position>size){
  return false;
}
  Node<T> *nodedelete=nullptr;//pointer to store node to be deleted
  //removing the first node
  if(position==1){
    nodedelete=first;
    first=first->getNext();//move pointer to next node

  }else{
    //moving through the node before the one to be deleted.
    Node<T> *pnode=first;
    for(size_t i=1;i<position-1;i++){
      pnode =pnode->getNext();

    }
    nodedelete=pnode->getNext();//node to delete
    pnode ->setNext(nodedelete->getNext());//update the previors node next ptr

  }

  delete nodedelete;//free memory of node that was removed
  size--;//decrease the size
  return true;


}

template <typename T>
void LinkedList<T>::clear()
{
  // TODO
  //removing nodes one by one
  while(!isEmpty()){
    //will always remove the first node 
    remove(1);
  }

}

template <typename T>
T LinkedList<T>::getEntry(std::size_t position) const
{
  //checking bounds of positons
  if(position<1||position>size){
    //throwing error if out of the range
    throw std::out_of_range("position out of range");

  }
  //starting from first node
  Node<T> *ptr = first;

//moving through required pos
  for(size_t i=1; i<position; i++){
    ptr=ptr->getNext();

  }
  return ptr->getItem();//reutrn item at that pos

}

template <typename T>
void LinkedList<T>::setEntry(std::size_t position, const T &newValue)
{
  //checking the bounds of posiotion
  if(position<1|| position>size){
    //throwing error if out of range
    throw std::out_of_range("position out of range");
  }

    Node<T> *ptr = first;//starting from first node
    //moving tbhrough tot he requried position
    for(size_t i=0; i<position-1;i++){
    ptr=ptr->getNext();
    
    }
    ptr->setItem (newValue);//setting new value/

    
  
}
