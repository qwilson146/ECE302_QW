#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "list.hpp"
#include "sort.hpp"

/* Provided test cases */
TEST_CASE("Sort: Test move entry", "[sorting]")
{
  List<int> lst;

  lst.insert(1, 100);
  lst.insert(2, 4);
  lst.insert(3, 10);
  lst.insert(4, 25);
  lst.insert(5, 11);

  // move forward
  lst.moveEntry(1, 3);

  REQUIRE(lst.getLength() == 5);
  REQUIRE(lst.getEntry(1) == 4);
  REQUIRE(lst.getEntry(2) == 10);
  REQUIRE(lst.getEntry(3) == 100);
  REQUIRE(lst.getEntry(4) == 25);
  REQUIRE(lst.getEntry(5) == 11);

  // move backward
  lst.moveEntry(5, 1);

  REQUIRE(lst.getLength() == 5);
  REQUIRE(lst.getEntry(1) == 11);
  REQUIRE(lst.getEntry(2) == 4);
  REQUIRE(lst.getEntry(3) == 10);
  REQUIRE(lst.getEntry(4) == 100);
  REQUIRE(lst.getEntry(5) == 25);
}

TEST_CASE("Sort: Integer sorting", "[sorting]")
{

  List<int> lst;

  lst.insert(1, 100);
  lst.insert(2, 4);
  lst.insert(3, 10);
  lst.insert(4, 25);
  lst.insert(5, 11);

  quick_sort(lst, 1, lst.getLength()); // note the change here!

  // check sorted list
  REQUIRE(lst.getEntry(1) == 4);
  REQUIRE(lst.getEntry(2) == 10);
  REQUIRE(lst.getEntry(3) == 11);
  REQUIRE(lst.getEntry(4) == 25);
  REQUIRE(lst.getEntry(5) == 100);
}

TEST_CASE("Sort: Test move entry throw", "[sorting]")
{
  List<int> lst;

  lst.insert(1, 100);
  lst.insert(2, 4);
  lst.insert(3, 10);
  lst.insert(4, 25);
  lst.insert(5, 11);

  // try to move forward
  REQUIRE_THROWS(lst.moveEntry(1, 6));
  REQUIRE_THROWS(lst.moveEntry(0, 5));

  lst.insert(5, 11);
  REQUIRE_NOTHROW(lst.moveEntry(1, 6));

  // try to move backward
  REQUIRE_THROWS(lst.moveEntry(7, 1));
  REQUIRE_THROWS(lst.moveEntry(6, -1));
}

/* Your test cases */

TEST_CASE("Quick Sort - Integers") {
  List<int> list;
  //varius values being put into list
  list.insert(1, 42);
  list.insert(2, 17);
  list.insert(3, 99);
  list.insert(4, 8);
  list.insert(5, 64);
  
  //sorting the list
  quick_sort(list, 1, list.getLength());
  
  //checking that the list is sorted alphabetically
  REQUIRE(list.getEntry(1) == 8);
  REQUIRE(list.getEntry(2) == 17);
  REQUIRE(list.getEntry(3) == 42);
  REQUIRE(list.getEntry(4) == 64);
  REQUIRE(list.getEntry(5) == 99);
}

TEST_CASE("Quick Sort - Characters") {
  List<char> list;
  //inserting varius characters into the list
  list.insert(1, 'z');
  list.insert(2, 'x');
  list.insert(3, 'y');
  list.insert(4, 'm');
  list.insert(5, 'a');
  
  //sorting list
  quick_sort(list, 1, list.getLength());
  
  //sorting the letters by alphabetical order
  REQUIRE(list.getEntry(1) == 'a');
  REQUIRE(list.getEntry(2) == 'm');
  REQUIRE(list.getEntry(3) == 'x');
  REQUIRE(list.getEntry(4) == 'y');
  REQUIRE(list.getEntry(5) == 'z');
}

TEST_CASE("Quick Sort Strings") {
  List<std::string> list;
  //inputting different car brands into the list
  list.insert(1, "Lamborghini");
  list.insert(2, "Pagani");
  list.insert(3, "Audi");
  list.insert(4, "Porsche");
  list.insert(5, "Ford");
  
  //sorting the list
  quick_sort(list, 1, list.getLength());
  
  //again alphabetical order
  REQUIRE(list.getEntry(1) == "Audi");
  REQUIRE(list.getEntry(2) == "Ford");
  REQUIRE(list.getEntry(3) == "Lamborghini");
  REQUIRE(list.getEntry(4) == "Pagani");
  REQUIRE(list.getEntry(5) == "Porsche");
}

TEST_CASE("Quick Sort Already Sorted") {
  List<int> list;
  //pre sorted list is inserted
  list.insert(1, 2);
  list.insert(2, 4);
  list.insert(3, 6);
  list.insert(4, 8);
  list.insert(5, 10);
  
  //quick sorting this again should not change the order in which they appear
  quick_sort(list, 1, list.getLength());
  
//checking that it did not alter the list
  REQUIRE(list.getEntry(1) == 2);
  REQUIRE(list.getEntry(2) == 4);
  REQUIRE(list.getEntry(3) == 6);
  REQUIRE(list.getEntry(4) == 8);
  REQUIRE(list.getEntry(5) == 10);
}

TEST_CASE("Quick Sort   Single Element List") {
  List<int> list;
  list.insert(1, 99);//one value getting input
  
  //should not change as ther is only 1
  quick_sort(list, 1, list.getLength());
  
  //checking no change
  REQUIRE(list.getEntry(1) == 99);
}

TEST_CASE("Quick Sort - Empty List") {
  List<int> list;
  //inputting nothing to list
  
  //sorting nothing
  quick_sort(list, 1, list.getLength());
  
  //should remain list empty
  REQUIRE(list.getLength() == 0);
}

TEST_CASE("Quick Sort Out of Range Indices") {
  List<int> list;
  //just throwing in values intp respective indices
  list.insert(1, 15);
  list.insert(2, 25);
  //should throw an error as these are not within the bounds.
  REQUIRE_THROWS_AS(quick_sort(list, 0, 2), std::out_of_range);
  REQUIRE_THROWS_AS(quick_sort(list, 1, 3), std::out_of_range);
}