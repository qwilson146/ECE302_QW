#include "graph.hpp"
#include <queue>


template <typename ItemType>
Graph<ItemType>::Graph()
{
  // TODO
  //dont need to add anything bc it will auto initialize
}

template <typename ItemType>
int Graph<ItemType>::getNumVertices() const
{
  // TODO
  //num of vertices is the size of the list
  return adjlist.size(); // Placeholder
}

template <typename ItemType>
int Graph<ItemType>::getNumEdges() const
{
  // TODO
  //setting edge count
  int totaledge = 0;
  //loop through vertex
  for (auto it=adjlist.begin();it!=adjlist.end();it++){
    //counting all vertices
    totaledge+=it->second.size();
  }
  //edges stored twice so divide by 2
  return totaledge/2;
}

template <typename ItemType>
bool Graph<ItemType>::add(ItemType start, ItemType end)
{
  //testing for self loops
  if (start == end) {
    return false;
}

// Ensure vertices exist 
  if (!adjlist.empty()) {
      bool exist = false;
      typename std::map<ItemType, std::set<ItemType>>::iterator it = adjlist.begin();
        //looping throguh list to find start or end
          while (it != adjlist.end()) {
              if (it->first == start || it->first == end) {
                 exist = true;//if one is found
              }
              ++it;
          }

        //no vertex = no edge
          if (!exist) {
            return false;
          }
}

  //checking for dups
  if (adjlist[start].count(end) || adjlist[end].count(start)) {
    return false; // Edge exists
  }

  // Add the edge
  adjlist[start].insert(end);
  adjlist[end].insert(start);

  return true; 

}

template <typename ItemType>
bool Graph<ItemType>::remove(ItemType start, ItemType end)
{
  // TODO
  if (adjlist[end].count(start) == 0 || adjlist[start].count(end) == 0) {
    return false; // Edge doesn't exist
  }

  // Remove the edge from both adj sets
  adjlist[start].erase(end);
  adjlist[end].erase(start);

  // Remove the vertices if they no longer adj vertices
  if (adjlist[start].empty()) {
    adjlist.erase(start);
  }
  if (adjlist[end].empty()) {
    adjlist.erase(end);
  }

return true;

   
}

template <typename ItemType>
void Graph<ItemType>::depthFirstTraversal(ItemType start, void visit(ItemType &))
{
  // BONUS TODO, you may need a stack and/or a recursive helper function
}

template <typename ItemType>
void Graph<ItemType>::breadthFirstTraversal(ItemType start, void visit(ItemType &))
{
  // BONUS TODO, you may need a queue and/or a recursive helper function
}