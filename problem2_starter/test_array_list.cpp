#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "array_list.hpp"

// force class expansion
template class ArrayList<int>;

TEST_CASE("Test", "[ArrayList]")
{
  ArrayList<int> list;
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

//NEW TEST CASES HERE

// Test case for the default constructor
TEST_CASE("ArrayList Default Constructor", "[ArrayList]") {
    ArrayList<int> list;
    REQUIRE(list.isEmpty());         // The list should be empty initially
    REQUIRE(list.getLength() == 0);  // Length should be 0
}

// Test case for inserting elements into the ArrayList
TEST_CASE("ArrayList Insert", "[ArrayList]") {
    ArrayList<int> list;

    REQUIRE(list.insert(1, 10));  // Insert at the beginning
    REQUIRE(list.insert(2, 20));  // Insert at the end
    REQUIRE(list.insert(2, 15));  // Insert in the middle

    REQUIRE(list.getLength() == 3);  // Should contain 3 elements
    REQUIRE(list.getEntry(1) == 10); // Check first element
    REQUIRE(list.getEntry(2) == 15); // Check second element
    REQUIRE(list.getEntry(3) == 20); // Check third element

    REQUIRE_FALSE(list.insert(0, 5));   // Invalid position (out of bounds)
    REQUIRE_FALSE(list.insert(5, 25));  // Invalid position (out of bounds)
}

// Test case for removing elements from the ArrayList
TEST_CASE("ArrayList Remove", "[ArrayList]") {
    ArrayList<int> list;

    list.insert(1, 10);
    list.insert(2, 20);
    list.insert(3, 30);

    REQUIRE(list.getLength() == 3);

    REQUIRE(list.remove(2));  // Remove middle element
    REQUIRE(list.getLength() == 2);
    REQUIRE(list.getEntry(1) == 10);
    REQUIRE(list.getEntry(2) == 30); // Ensure shift

    REQUIRE(list.remove(1));  // Remove element
    REQUIRE(list.getLength() == 1);
    REQUIRE(list.getEntry(1) == 30); // element should be there

    REQUIRE(list.remove(1));  // Remove last element
    REQUIRE(list.isEmpty());  // The list should be empty now

    REQUIRE_FALSE(list.remove(1)); // Invalid removal (out of bounds)
}

// Test case for checking if the list is empty
TEST_CASE("ArrayList isEmpty", "[ArrayList]") {
    ArrayList<int> list;
    REQUIRE(list.isEmpty());

    list.insert(1, 10);
    REQUIRE_FALSE(list.isEmpty());

    list.remove(1);
    REQUIRE(list.isEmpty());
}

// Test case for getting the length of the list
TEST_CASE("ArrayList getLength", "[ArrayList]") {
    ArrayList<int> list;

    REQUIRE(list.getLength() == 0);

    list.insert(1, 10);
    REQUIRE(list.getLength() == 1);

    list.insert(2, 20);
    REQUIRE(list.getLength() == 2);

    list.remove(1);
    REQUIRE(list.getLength() == 1);
}

// Test case for retrieving an entry from the list
TEST_CASE("ArrayList getEntry", "[ArrayList]") {
    ArrayList<int> list;
    list.insert(1, 10);
    list.insert(2, 20);
    list.insert(3, 30);

    REQUIRE(list.getEntry(1) == 10);
    REQUIRE(list.getEntry(2) == 20);
    REQUIRE(list.getEntry(3) == 30);
}

// Test case for setting an entry in the list
TEST_CASE("ArrayList setEntry", "[ArrayList]") {
    ArrayList<int> list;
    list.insert(1, 10);
    list.insert(2, 20);
    list.insert(3, 30);

    list.setEntry(2, 25); // Update element

    REQUIRE(list.getEntry(1) == 10);
    REQUIRE(list.getEntry(2) == 25); // Ensure value updated
    REQUIRE(list.getEntry(3) == 30);
}

// Test case for clearing the list
TEST_CASE("ArrayList Clear", "[ArrayList]") {
    ArrayList<int> list;
    list.insert(1, 10);
    list.insert(2, 20);

    REQUIRE(list.getLength() == 2);

    list.clear();
    REQUIRE(list.isEmpty());
    REQUIRE(list.getLength() == 0);
}

// Test case for the copy constructor
TEST_CASE("ArrayList Copy Constructor", "[ArrayList]") {
    ArrayList<int> list;
    list.insert(1, 10);
    list.insert(2, 20);
    list.insert(3, 30);

    ArrayList<int> copy(list); // Use copy constructor

    REQUIRE(copy.getLength() == 3);
    REQUIRE(copy.getEntry(1) == 10);
    REQUIRE(copy.getEntry(2) == 20);
    REQUIRE(copy.getEntry(3) == 30);
}

// Test case for the assignment operator
TEST_CASE("ArrayList Assignment Operator", "[ArrayList]") {
    ArrayList<int> list1;
    list1.insert(1, 10);
    list1.insert(2, 20);

    ArrayList<int> list2;
    list2.insert(1, 50);
    list2.insert(2, 60);
    list2.insert(3, 70);

    list2 = list1; // Use assignment operator

    REQUIRE(list2.getLength() == 2);
    REQUIRE(list2.getEntry(1) == 10);
    REQUIRE(list2.getEntry(2) == 20);
}
