#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "ArrayMaxHeap.hpp"

/* Provided test cases */
TEST_CASE("Heap: test construct from array", "[construct]")
{
   int array[] = {80, 70, 60, 50, 40, 30, 20, 10};
   ArrayMaxHeap<int> heap(array, 8);
   REQUIRE(heap.getNumberOfNodes() == 8);
   REQUIRE(heap.getHeight() == 4);
   REQUIRE(heap.isEmpty() == false);
   heap.clear();
   REQUIRE(heap.getNumberOfNodes() == 0);
   REQUIRE(heap.getHeight() == 0);
   REQUIRE(heap.isEmpty() == true);
}

TEST_CASE("Heap: test heap sort", "[sort]")
{
   int array[] = {15, 5, 20, 10, 30};
   ArrayMaxHeap<int> heap(array, 5);
   heap.heapSort(array, 5);
   REQUIRE(array[0] == 30);
   REQUIRE(array[1] == 20);
   REQUIRE(array[2] == 15);
   REQUIRE(array[3] == 10);
   REQUIRE(array[4] == 5);
}


/* Additional test cases */





TEST_CASE("heap test add duplicate", "[add]")
{
   ArrayMaxHeap<int> heap;
   REQUIRE(heap.add(42) == true);  // Add first time
   REQUIRE(heap.add(42) == false); // Duplicate not allowed
}



TEST_CASE("heap test frequent add and remove", "[stress]")
{
   ArrayMaxHeap<int> heap;
   for (int i = 0; i < 100; i++){
      REQUIRE(heap.add(i) == true);
      REQUIRE(heap.remove() == true);
   }
   REQUIRE(heap.isEmpty() == true);
}

TEST_CASE("heap test peek on empty heap throws", "[peek][exception]")
{
   ArrayMaxHeap<int> heap;
   REQUIRE_THROWS_AS(heap.peekTop(), std::out_of_range);
}

TEST_CASE("hea test remove from empty heap", "[remove][edge]")
{
   ArrayMaxHeap<int> heap;
   REQUIRE(heap.remove() == false);
}

TEST_CASE("hep add multiple and peek maintains max", "[peek][add]")
{
   ArrayMaxHeap<int> heap;
   REQUIRE(heap.add(10) == true);
   REQUIRE(heap.add(50) == true);
   REQUIRE(heap.add(20) == true);
   REQUIRE(heap.peekTop() == 50); 
}

TEST_CASE("heap test clear resets everything", "[clear]")
{
   ArrayMaxHeap<int> heap;
   heap.add(1);
   heap.add(2);
   heap.add(3);
   heap.clear();
   REQUIRE(heap.isEmpty() == true);
   REQUIRE(heap.getNumberOfNodes() == 0);
   REQUIRE_THROWS_AS(heap.peekTop(), std::out_of_range);
}

TEST_CASE("ehap test getHeight on an empty heap", "[height][edge]")
{
   ArrayMaxHeap<int> heap;
   REQUIRE(heap.getHeight() == 0); 
}

TEST_CASE("hepa test getHeight on non-empty heap", "[height]")
{
   ArrayMaxHeap<int> heap;
   heap.add(10);
   heap.add(20);
   heap.add(30);
   REQUIRE(heap.getHeight() == 2);
}

TEST_CASE("heap test getNumberOfNodes updates correctly", "[nodes]")
{
   ArrayMaxHeap<int> heap;
   REQUIRE(heap.getNumberOfNodes() == 0);
   heap.add(5);
   heap.add(10);
   heap.add(20);
   REQUIRE(heap.getNumberOfNodes() == 3); // Should be 3
}

TEST_CASE("heap test sort with invalid input size", "[sort][exception]")
{
   int array[200];  
   for (int i = 0; i < 200; i++){
      array[i] = i;
   }
   ArrayMaxHeap<int> heap;
   REQUIRE_THROWS_AS(heap.heapSort(array, 200), std::invalid_argument);
}

TEST_CASE("heap test sort with duplicates throws", "[sort][exception]")
{
   int array[] = {1, 2, 3, 2}; // Duplicate 2
   ArrayMaxHeap<int> heap;
   REQUIRE_THROWS_AS(heap.heapSort(array, 4), std::invalid_argument);
}

TEST_CASE("heap test add multiple elements", "[add][multiple]")
{
   ArrayMaxHeap<int> heap;
   for (int i = 0; i < 10; i++){
      REQUIRE(heap.add(i) == true);
   }

   REQUIRE(heap.peekTop() == 9); 
}

TEST_CASE("heap test remove multiple elements", "[remove][multiple]")
{
   ArrayMaxHeap<int> heap;
   for (int i = 0; i < 10; i++){
      heap.add(i);
   }

   for (int i = 9; i >= 0; i--){
      REQUIRE(heap.peekTop() == i); 
      REQUIRE(heap.remove() == true);
   }
   REQUIRE(heap.isEmpty() == true);
}

