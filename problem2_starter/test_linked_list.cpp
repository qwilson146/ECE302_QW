#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "linked_list.hpp"

template class LinkedList<int>;

TEST_CASE("TODO", "[LinkedList]")
{
    LinkedList<int> list;
    REQUIRE(list.isEmpty());

  REQUIRE_FALSE(list.insert(0, 0));    // invalid
  REQUIRE(list.isEmpty());             // still empty

  REQUIRE(list.insert(1, 1));          // valid
  REQUIRE(list.getLength() == 1);      // length is 1

  REQUIRE_FALSE(list.remove(0));       // invalid
  REQUIRE(list.getLength() == 1);      // length is still 1

  REQUIRE(list.remove(1));             // valid
  REQUIRE(list.isEmpty());             // now empty

  list.insert(1, 301);
  list.insert(2, 302);

  REQUIRE(list.getEntry(1) == 301);
  REQUIRE(list.getEntry(2) == 302);

  REQUIRE_THROWS_AS(list.getEntry(0), std::out_of_range);
  REQUIRE_THROWS_AS(list.setEntry(0, 300), std::out_of_range);

  // pos = 1 is the first item, that also indicates pos = n is the last item
  // insertion at pos=n should be valid, and insertion at pos=n+1 also being valid
  // removal at pos=1 is valid, but removal at pos=n+1 is invalid
}




//NEW TEST CASES BELOW


TEST_CASE("LinkedList Constructor initializes an empty list", "[LinkedList]") {
    LinkedList<int> list;
    REQUIRE(list.isEmpty()); // List should be empty
    REQUIRE(list.getLength() == 0); // Size should be 0
}

TEST_CASE("Insert method correctly inserts elements at valid positions", "[LinkedList]") {
    LinkedList<int> list;

    REQUIRE(list.insert(1, 10)); // Insert at pos 1
    REQUIRE(list.getEntry(1) == 10);
    REQUIRE(list.getLength() == 1);

    REQUIRE(list.insert(2, 20)); // Insert at pos 2
    REQUIRE(list.getEntry(2) == 20);
    REQUIRE(list.getLength() == 2);

    REQUIRE(list.insert(1, 5)); // Insert at beginning
    REQUIRE(list.getEntry(1) == 5);
    REQUIRE(list.getEntry(2) == 10);
    REQUIRE(list.getEntry(3) == 20);
    REQUIRE(list.getLength() == 3);

    REQUIRE_FALSE(list.insert(5, 30)); // Invalid position
}

TEST_CASE("Remove method correctly removes elements from valid positions", "[LinkedList]") {
    LinkedList<int> list;
    list.insert(1, 10);
    list.insert(2, 20);
    list.insert(3, 30);

    REQUIRE(list.remove(2)); // Remove middle element
    REQUIRE(list.getLength() == 2);
    REQUIRE(list.getEntry(1) == 10);
    REQUIRE(list.getEntry(2) == 30);

    REQUIRE(list.remove(1)); // Remove first element
    REQUIRE(list.getLength() == 1);
    REQUIRE(list.getEntry(1) == 30);

    REQUIRE(list.remove(1)); // Remove last remaining element
    REQUIRE(list.isEmpty());

    REQUIRE_FALSE(list.remove(1)); // Invalid position
}

TEST_CASE("getEntry method retrieves correct values", "[LinkedList]") {
    LinkedList<int> list;
    list.insert(1, 10);
    list.insert(2, 20);
    list.insert(3, 30);

    REQUIRE(list.getEntry(1) == 10);
    REQUIRE(list.getEntry(2) == 20);
    REQUIRE(list.getEntry(3) == 30);

    REQUIRE_THROWS_AS(list.getEntry(4), std::out_of_range); // Invalid position
}

TEST_CASE("setEntry method updates values correctly", "[LinkedList]") {
    LinkedList<int> list;
    list.insert(1, 10);
    list.insert(2, 20);
    list.insert(3, 30);

    list.setEntry(2, 50);
    REQUIRE(list.getEntry(2) == 50);

    list.setEntry(1, 5);
    REQUIRE(list.getEntry(1) == 5);

    list.setEntry(3, 100);
    REQUIRE(list.getEntry(3) == 100);

    REQUIRE_THROWS_AS(list.setEntry(4, 200), std::out_of_range); // Invalid position
}

TEST_CASE("isEmpty method returns correct status", "[LinkedList]") {
    LinkedList<int> list;
    REQUIRE(list.isEmpty()); // empty

    list.insert(1, 10);
    REQUIRE_FALSE(list.isEmpty()); // Now elements are contained within

    list.remove(1);
    REQUIRE(list.isEmpty()); // Empty
}

TEST_CASE("getLength method returns the correct size", "[LinkedList]") {
    LinkedList<int> list;
    REQUIRE(list.getLength() == 0);

    list.insert(1, 10);
    REQUIRE(list.getLength() == 1);

    list.insert(2, 20);
    REQUIRE(list.getLength() == 2);

    list.remove(1);
    REQUIRE(list.getLength() == 1);
}

TEST_CASE("clear method removes all elements", "[LinkedList]") {
    LinkedList<int> list;
    list.insert(1, 10);
    list.insert(2, 20);
    list.insert(3, 30);

    list.clear();
    REQUIRE(list.isEmpty());
    REQUIRE(list.getLength() == 0);

    REQUIRE_FALSE(list.remove(1)); // Should not be able to remove from an empty list
}

TEST_CASE("Copy constructor creates a correct deep copy", "[LinkedList]") {
    LinkedList<int> original;
    original.insert(1, 10);
    original.insert(2, 20);
    original.insert(3, 30);

    LinkedList<int> copy(original);

    REQUIRE(copy.getLength() == original.getLength());
    REQUIRE(copy.getEntry(1) == original.getEntry(1));
    REQUIRE(copy.getEntry(2) == original.getEntry(2));
    REQUIRE(copy.getEntry(3) == original.getEntry(3));

    // change original (no changes should be made in the copy though)
    original.setEntry(1, 100);
    REQUIRE(copy.getEntry(1) == 10);
}

TEST_CASE("Copy assignment operator correctly copies data", "[LinkedList]") {
    LinkedList<int> list1;
    list1.insert(1, 10);
    list1.insert(2, 20);

    LinkedList<int> list2;
    list2.insert(1, 5);
    list2.insert(2, 15);
    list2.insert(3, 25);

    list2 = list1; // copy lists 1 and 2

    REQUIRE(list2.getLength() == list1.getLength());
    REQUIRE(list2.getEntry(1) == list1.getEntry(1));
    REQUIRE(list2.getEntry(2) == list1.getEntry(2));

    // Modify list1 and ensure list2 unchanged
    list1.setEntry(1, 50);
    REQUIRE(list2.getEntry(1) == 10);
}

TEST_CASE("swap method correctly swaps two lists", "[LinkedList]") {
    LinkedList<int> list1;
    list1.insert(1, 10);
    list1.insert(2, 20);

    LinkedList<int> list2;
    list2.insert(1, 5);
    list2.insert(2, 15);
    list2.insert(3, 25);

    list1.swap(list2);

    // list1 have list2's elements
    REQUIRE(list1.getLength() == 3);
    REQUIRE(list1.getEntry(1) == 5);
    REQUIRE(list1.getEntry(2) == 15);
    REQUIRE(list1.getEntry(3) == 25);

    // list2 have list1's elements
    REQUIRE(list2.getLength() == 2);
    REQUIRE(list2.getEntry(1) == 10);
    REQUIRE(list2.getEntry(2) == 20);
}