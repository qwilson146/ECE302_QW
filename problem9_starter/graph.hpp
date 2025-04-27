#ifndef _GRAPH_H_
#define _GRAPH_H_
//needs lib to use map and set
#include <map>
#include <set>

#include "abstract_graph.hpp"

template <typename ItemType>
class Graph : public AbstractGraph<ItemType>
{
private:
    // Add your private members here
    // Using an adjacency list or adjacency matrix, not linked-based vertices

    //will use adjacent list
    std::map<ItemType,std::set<ItemType>> adjlist;



    // For adjacency matrix, you may use a 2D array, or a vector of vectors etc and an array of vertices to map the indices to vertices
    // For adjacency list, you may use a std::map to map vertices to the set of adjacent vertices
    // Refer to std::vector, std::set, std::map, std::unordered_map etc
public:
    Graph();

    int getNumVertices() const;

    int getNumEdges() const;

    bool add(ItemType start, ItemType end);

    bool remove(ItemType start, ItemType end);

    void depthFirstTraversal(ItemType start, void visit(ItemType &));

    void breadthFirstTraversal(ItemType start, void visit(ItemType &));
};

#include "graph.tpp"

#endif
