#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "limited_size_bag.hpp"

// force template expansion for ints
template class LimitedSizeBag<int>;

TEST_CASE("Calling all public members", "[LimitedSizeBag]")
{
  LimitedSizeBag<int> b;

  b.add(0);
  b.remove(0);
  b.isEmpty();
  b.getCurrentSize();
  b.clear();
  b.getFrequencyOf(0);
  b.contains(0);
}


TEST_CASE("Adding items to the bag", "[LimitedSizeBag]")
{
  LimitedSizeBag<int> b;

  REQUIRE(b.add(0) == true);  // should pass bc not full
  REQUIRE(b.getCurrentSize() == 1);  // size should now b 1

  // Adding items until max size is reached
  for (std::size_t i = 1; i < 100; ++i)
  {
    REQUIRE(b.add(i) == true);
  }
  REQUIRE(b.getCurrentSize() == 100);  // size should be 100 now
  REQUIRE(b.add(100) == false);  // should fail as max size is 100
}

TEST_CASE("Removing items from the bag", "[LimitedSizeBag]")
{
  LimitedSizeBag<int> b;
  //adding items to bag to initialize it
  b.add(10);
  b.add(20);
  b.add(30);

  REQUIRE(b.getCurrentSize() == 3);
  REQUIRE(b.remove(20) == true);  // should succeed as removed 20 from bag
  REQUIRE(b.getCurrentSize() == 2);  // size should decrease
  REQUIRE(b.remove(40) == false);  // should fail as #40 is not in the bag
}

TEST_CASE("Checking if the bag is empty", "[LimitedSizeBag]")
{
  LimitedSizeBag<int> b;

  REQUIRE(b.isEmpty() == true);  // should be true initially bc no elements within
  b.add(5); //added 5 in
  REQUIRE(b.isEmpty() == false);  // should be false after adding an item 5
  b.clear();//clear the bag out of items
  REQUIRE(b.isEmpty() == true);  // should be true after clearing ie no items inside
}

TEST_CASE("Getting frequency of an item", "[LimitedSizeBag]")
{
  LimitedSizeBag<int> b;
  b.add(5);
  b.add(10);
  b.add(5);

  REQUIRE(b.getFrequencyOf(5) == 2);  // should return 2 as 5 is added twice
  REQUIRE(b.getFrequencyOf(10) == 1);  // should return 1 as 10 is added once
  REQUIRE(b.getFrequencyOf(20) == 0);  // should return 0 as 20 is not in the bag
}

TEST_CASE("Checking if the bag contains an item", "[LimitedSizeBag]")
{
  LimitedSizeBag<int> b;
  b.add(100);
  b.add(200);

  REQUIRE(b.contains(100) == true);  // should return true as it contains 100
  REQUIRE(b.contains(300) == false);  // should return false as 300 is not in the bag (only 100,200)
}

TEST_CASE("Equality operator", "[LimitedSizeBag]")
{
  LimitedSizeBag<int> b1;
  LimitedSizeBag<int> b2;

  b1.add(1);
  b1.add(2);
  b2.add(1);
  b2.add(2);

  REQUIRE(b1 == b2);  // should be equal as both bags have the same items

  b2.add(3);  // b2 now has an extra item
  REQUIRE(b1 == b2);  // should be false because the bags are different (b2 has 1 more)
  b2.remove(3);  // remove the extra item from b2 
  REQUIRE(b1 == b2);  // should be equal again as 3 is not in either. only same elements r contained
}

TEST_CASE("Clearing the bag", "[LimitedSizeBag]")
{
  LimitedSizeBag<int> b;
  b.add(5);
  b.add(10);
  b.add(15);

  REQUIRE(b.getCurrentSize() == 3);  // should be 3 before clearing
  b.clear();
  REQUIRE(b.getCurrentSize() == 0);  // should be 0 after clearing
}