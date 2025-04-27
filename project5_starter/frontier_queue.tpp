#include "frontier_queue.hpp"

template <typename T>
State<T> frontier_queue<T>::pop()
{

  // TODO: implement this the same way we implemented pop in the heap lecture. Compare states using getFCost.
  State<T> removed = queue.front();
  queue[0]=queue.back();
  queue.pop_back();

  int current =0;
  while (true)
  {
    int leftkid = 2 * current + 1;
    int rightkid = 2 * current + 2;
    int min = current;

    if (leftkid < queue.size() && queue[leftkid].getFCost() < queue[min].getFCost()) {
      min = leftkid;
    }
    if (rightkid < queue.size() && queue[rightkid].getFCost() < queue[min].getFCost()) {
      min = rightkid;
    }

    if (min != current) {
      std::swap(queue[current], queue[min]);
      current = min;
    } else {
      break;
    }
  }

  return removed;
}

template <typename T>
void frontier_queue<T>::push(const T &p, std::size_t cost, std::size_t heur)
{

  // TODO: implement this the same way we implemented push in the heap lecture.
  
  State<T> pushed(p, cost, heur);
  queue.push_back(pushed);
  int current = queue.size() - 1;
  
  while(current >0) {
    int par=(current - 1) / 2;
    if(queue[par].getFCost() > pushed.getFCost()){
      queue[current] = queue[par];  // Move parent down
      current = par;                // Move up
    }else
    {
      break;
    }
  }

  queue[current] = pushed;  
}

template <typename T>
bool frontier_queue<T>::empty()
{

  // TODO

  return queue.size()==0;
}

template <typename T>
bool frontier_queue<T>::contains(const T &p)
{

  // TODO
  if(queue.empty()){
    return false;
  }

  for( int i=0;i<queue.size();i++){
    if(queue[i].getValue()==p){
      return true;
    }
  }

  return false;
}

template <typename T>
void frontier_queue<T>::replaceif(const T &p, std::size_t cost)
{

  // TODO
  for (int i = 0; i < queue.size(); i++){
    if (queue[i].getValue() == p){
      if (cost < queue[i].getPathCost()){
        std::size_t heur = queue[i].getFCost() - queue[i].getPathCost();
        queue[i].updatePathCost(cost); 
        int current = i;
        while (current > 0){
          int par = (current - 1) / 2;
          if (queue[par].getFCost() > queue[current].getFCost()){
            std::swap(queue[par], queue[current]);
            current = par;
            }else
            {
              break;
            }
        }
      }
          break;
    }
  }

  
}
