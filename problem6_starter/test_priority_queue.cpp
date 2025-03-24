#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "list.hpp"
#include "sorted_list.hpp"
#include "priority_queue.hpp"

typedef SortedList<int, List<int>> SortedListType;
typedef PriorityQueue<int, SortedListType> PriorityQueueType;

/* Provided test cases */
TEST_CASE("Priority: Testing Sorted List", "[sorted list]")
{
  SortedList<int, List<int>> sort;

  REQUIRE(sort.isEmpty());
  REQUIRE(sort.getLength() == 0);

  sort.insert(1);
  REQUIRE_FALSE(sort.isEmpty());
  REQUIRE(sort.getLength() == 1);
  sort.insert(2);
  REQUIRE(sort.getLength() == 2);
  sort.insert(8);
  REQUIRE(sort.getLength() == 3);
  sort.insert(6);
  REQUIRE(sort.getLength() == 4);
  sort.insert(9);
  REQUIRE(sort.getLength() == 5);
  sort.insert(0);
  REQUIRE(sort.getLength() == 6);

  REQUIRE(sort.getEntry(1) == 0);
  REQUIRE(sort.getPosition(0) == 1);
  REQUIRE(sort.getEntry(2) == 1);
  REQUIRE(sort.getPosition(1) == 2);
  REQUIRE(sort.getEntry(3) == 2);
  REQUIRE(sort.getPosition(2) == 3);
  REQUIRE(sort.getEntry(4) == 6);
  REQUIRE(sort.getPosition(6) == 4);
  REQUIRE(sort.getEntry(5) == 8);
  REQUIRE(sort.getPosition(8) == 5);
  REQUIRE(sort.getEntry(6) == 9);
  REQUIRE(sort.getPosition(9) == 6);

  sort.remove(0);
  REQUIRE(sort.getEntry(1) == 1);
  REQUIRE(sort.getLength() == 5);

  sort.remove(1);
  REQUIRE(sort.getEntry(1) == 2);
  REQUIRE(sort.getLength() == 4);

  sort.remove(9);
  REQUIRE(sort.getEntry(1) == 2);
  REQUIRE(sort.getLength() == 3);

  sort.removeAt(2);
  REQUIRE(sort.getEntry(1) == 2);
  REQUIRE(sort.getLength() == 2);

  sort.removeAt(1);
  REQUIRE(sort.getEntry(1) == 8);
  REQUIRE(sort.getLength() == 1);

  sort.removeAt(1);
  REQUIRE(sort.getLength() == 0);
  REQUIRE(sort.isEmpty());
}

TEST_CASE("Priority: Testing Priority Queue Add/isEmpty/peek/remove", "[priority queue]")
{
  PriorityQueueType pq;

  REQUIRE(pq.isEmpty());

  pq.add(3);
  REQUIRE_FALSE(pq.isEmpty());

  pq.add(1);
  pq.add(5);
  pq.add(2);
  REQUIRE(pq.peek() == 5);

  pq.remove();
  REQUIRE(pq.peek() == 3);

  pq.remove();
  REQUIRE(pq.peek() == 2);
}


TEST_CASE("Priority: Testing Sorted List with random and duplicate values", "[sorted list]")
{
  SortedList<int, List<int>> sort;

 
  sort.insert(37);
  sort.insert(2);
  sort.insert(89);
  sort.insert(14);
  sort.insert(37); 
  sort.insert(-9);
  sort.insert(56);
  sort.insert(12);
  sort.insert(2);  

  REQUIRE(sort.getLength() == 9); 

  REQUIRE(sort.getEntry(1) == -9);
  REQUIRE(sort.getEntry(2) == 2);
  REQUIRE(sort.getEntry(3) == 2); 
  REQUIRE(sort.getEntry(4) == 12);
  REQUIRE(sort.getEntry(5) == 14);
  REQUIRE(sort.getEntry(6) == 37);
  REQUIRE(sort.getEntry(7) == 37); 
  REQUIRE(sort.getEntry(8) == 56);
  REQUIRE(sort.getPosition(-9) == 1);
  REQUIRE(sort.getPosition(14) == 5);


  sort.remove(2);
  REQUIRE(sort.getEntry(3) == 12);
  REQUIRE(sort.getLength() == 7);


  sort.removeAt(1);
  sort.removeAt(1);
  sort.removeAt(1);
  sort.removeAt(1);
  sort.removeAt(1);
  sort.removeAt(1);
  REQUIRE(sort.isEmpty());
}

TEST_CASE("Priority: Testing SortedList with large random values", "[sorted list]")
{
  SortedList<int, List<int>> sort;

  sort.insert(9234);
  sort.insert(2341);
  sort.insert(8099);
  sort.insert(4923);
  sort.insert(1234);
  sort.insert(9876);
  sort.insert(7123);
  sort.insert(4389);
  sort.insert(2100);

  REQUIRE(sort.getLength() == 9);  

  REQUIRE(sort.getEntry(1) == 1234);
  REQUIRE(sort.getEntry(9) == 9876);

  sort.remove(1234);
  sort.remove(9876);
  REQUIRE(sort.getLength() == 7); 
}

TEST_CASE("Priority: Testing Priority Queue with random values", "[priority queue]")
{
  PriorityQueueType pq;

  // Insert random values
  pq.add(325);
  pq.add(750);
  pq.add(85);
  pq.add(902);
  pq.add(487);

  REQUIRE(pq.peek() == 902);

  pq.remove();
  REQUIRE(pq.peek() == 750); 

  pq.remove();
  REQUIRE(pq.peek() == 487);

  pq.remove();
  pq.remove();
  pq.remove();
  REQUIRE(pq.peek() == 85); 
}

TEST_CASE("Priority: Testing Priority Queue with random order", "[priority queue]")
{
  PriorityQueueType pq;

  pq.add(920);
  pq.add(307);
  pq.add(570);
  pq.add(115);
  pq.add(888);

  REQUIRE(pq.peek() == 920); 

  pq.remove();
  REQUIRE(pq.peek() == 888);

  pq.remove();
  REQUIRE(pq.peek() == 570); 

  pq.remove();
  pq.remove();
  pq.remove();
  REQUIRE(pq.isEmpty()); 
}


TEST_CASE("Priority: Testing Priority Queue with mixed random values", "[priority queue]")
{
  PriorityQueueType pq;

  
  pq.add(589);
  pq.add(150);
  pq.add(922);
  pq.add(371);
  pq.add(456);

  REQUIRE(pq.peek() == 922);

  pq.remove();
  REQUIRE(pq.peek() == 589);

  pq.remove();
  REQUIRE(pq.peek() == 456);  

  pq.remove();
  pq.remove();
  pq.remove();
  REQUIRE(pq.isEmpty()); 
}