/** @file Stack.tpp */
// Finish this .tpp first to pass the first 3 unit tests

#include <stdexcept>
#include "Stack.hpp"
#include "Node.hpp"

template <typename ItemType>
Stack<ItemType>::Stack()
{
	// TODO
	headPtr=nullptr;
	currentSize=0;

} // end default constructor

template <typename ItemType>
Stack<ItemType>::~Stack()
{
	// TODO
	clear();

} // end destructor

template <typename ItemType>
bool Stack<ItemType>::isEmpty() const
{
	// TODO
	return currentSize==0;
} // end isEmpty

template <typename ItemType>
int Stack<ItemType>::size() const
{
	// TODO
	return currentSize;
} // end size

template <typename ItemType>
bool Stack<ItemType>::push(const ItemType &newItem)
{
	// TODO
	//creating a newer node that will hold a new item in the stack
	Node<ItemType>* newernode = new Node<ItemType> (newItem,headPtr);
	//updating the head ptr to the newer node that was just created
	headPtr=newernode;
	//updating the size to account for the newer node that was just added.
	currentSize++;

	return true;
} // end push

template <typename ItemType>
ItemType Stack<ItemType>::peek() const
{
	// TODO
	//checking if the stack is empty cause if it is you cannot peek into thestack
	if(currentSize<=0||headPtr==nullptr){
		throw std::logic_error("cannot peek empty stack");
	}
	//will return the item that is at the top of the stack if it is not empty (which was tested above)
	//
	return headPtr-> getItem();
} // end peek

template <typename ItemType>
bool Stack<ItemType>::pop()
{
	// TODO
	//checking if stack is empty and returning false if it is cause you cannot remove from
	//empty stack
	if(currentSize<=0||headPtr==nullptr){
		return false;
	}
	//storing current node in temp var to delete
	Node<ItemType>* Deletenode=headPtr;
	//head ptr pointing to next node which is the second item
	headPtr=headPtr->getNext();
	//dleteing the top node (stack) as it will be removed and no longer apart of stacl
	delete Deletenode;
	//decrementing the size to account for the deleted stack item
	currentSize--;
	//returning true if an item was removed successfully without error
	return true;
} // end pop

template <typename ItemType>
void Stack<ItemType>::clear()
{
	// TODO
	Node<ItemType>* ptr = headPtr;
    
    while (ptr != nullptr)
    {
        Node<ItemType>* tmp = ptr;    // Store the current node in a temporary pointer
        ptr = ptr->getNext();         // Move to the next node
        delete tmp;                   // Delete the current node
    }

    // After deleting all nodes, resethead pointer size
    headPtr = nullptr;
    currentSize = 0;
	
} // end clear