#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "dynamic_bag.hpp"

// force template expansion for ints
template class DynamicBag<int>;

TEST_CASE("Calling all public members", "[DynamicBag]")
{
  //original test case provided.
  DynamicBag<int> b;

  b.add(0);
  b.remove(0);
  b.isEmpty();
  b.getCurrentSize();
  b.clear();
  b.getFrequencyOf(0);
  b.contains(0);
}

//new test cases below

TEST_CASE("DynamicBag default constructor creates an empty bag", "[DynamicBag]")
{ 
  //empty bag and require it to b empty
    DynamicBag<int> bag;
    REQUIRE(bag.isEmpty());
    REQUIRE(bag.getCurrentSize() == 0);
}

TEST_CASE("DynamicBag add method adds elements to the bag", "[DynamicBag]")
{
    DynamicBag<int> bag;
    REQUIRE(bag.add(5)); // Add a single element
    REQUIRE_FALSE(bag.isEmpty());
    REQUIRE(bag.getCurrentSize() == 1);
    REQUIRE(bag.contains(5));

    // Add multiple elements and make sure added in correctly 
    REQUIRE(bag.add(10));
    REQUIRE(bag.add(15));
    REQUIRE(bag.getCurrentSize() == 3);
    REQUIRE(bag.contains(10));
    REQUIRE(bag.contains(15));
}

TEST_CASE("DynamicBag remove method removes elements", "[DynamicBag]")
{
    DynamicBag<int> bag;
    bag.add(5);
    bag.add(10);
    REQUIRE(bag.getCurrentSize() == 2);
    REQUIRE(bag.remove(5)); // Remove an existing element from bag
    REQUIRE_FALSE(bag.contains(5));
    REQUIRE(bag.getCurrentSize() == 1);

    REQUIRE_FALSE(bag.remove(42)); // Attempt to remove a non occuring element
    REQUIRE(bag.getCurrentSize() == 1);
}

TEST_CASE("DynamicBag clear method empties the bag", "[DynamicBag]")
{
    DynamicBag<int> bag;
    //add to bag to not be emtpy
    bag.add(1);
    bag.add(2);
    bag.add(3);
    //should not be empty now
    REQUIRE_FALSE(bag.isEmpty());
    //clear the bag
    bag.clear();
    //should now be empty and have no size to it
    REQUIRE(bag.isEmpty());

    REQUIRE(bag.getCurrentSize() == 0);
}

TEST_CASE("DynamicBag contains method checks for elements in the bag", "[DynamicBag]")
{
    DynamicBag<int> bag;
    //added 5 to bag
    bag.add(5);
    //make sure 5 is in
    REQUIRE(bag.contains(5));
    //random num that should NOT be in bag
    REQUIRE_FALSE(bag.contains(10));
}

TEST_CASE("DynamicBag getFrequencyOf method counts occurrences", "[DynamicBag]")
{
    DynamicBag<int> bag;
    // two 5s one 10
    bag.add(5);
    bag.add(5);
    bag.add(10);
    //require frequency to be calculated correctly
    REQUIRE(bag.getFrequencyOf(5) == 2);
    REQUIRE(bag.getFrequencyOf(10) == 1);
    REQUIRE(bag.getFrequencyOf(15) == 0);
}

TEST_CASE("DynamicBag operator== checks equality between bags", "[DynamicBag]")
{
    DynamicBag<int> bag1, bag2;

    REQUIRE(bag1 == bag2); // Both are empty

    bag1.add(5);
    bag2.add(5);
    REQUIRE(bag1 == bag2); // Same elements

    bag1.add(10);
    REQUIRE_FALSE(bag1 == bag2); // Different sizes

    bag2.add(10);
    REQUIRE(bag1 == bag2); // Same elements again

  
}

TEST_CASE("DynamicBag copy constructor creating copy", "[DynamicBag]")
{
    DynamicBag<int> bag1;
    bag1.add(5);
    bag1.add(10);

    DynamicBag<int> bag2 = bag1; // Copy constructor
    REQUIRE(bag2.getCurrentSize() == bag1.getCurrentSize());
    REQUIRE(bag2.contains(5));
    REQUIRE(bag2.contains(10));

    // Verify deep copy
    bag1.add(15);
    REQUIRE_FALSE(bag2.contains(15));
}

TEST_CASE("DynamicBag copy assignment creating copy", "[DynamicBag]")
{
    DynamicBag<int> bag1;
    //adding 5 and 10 in bag 1 
    bag1.add(5);
    bag1.add(10);

    DynamicBag<int> bag2;
    bag2 = bag1; // Copy assignment to bag 2
    REQUIRE(bag2.getCurrentSize() == bag1.getCurrentSize());
    REQUIRE(bag2.contains(5));
    REQUIRE(bag2.contains(10));

    // Verify deep copy
    bag1.add(15);
    REQUIRE_FALSE(bag2.contains(15));
}





