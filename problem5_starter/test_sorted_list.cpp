#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "sorted_list.hpp"
#include "list.hpp"

/* Provided tests */
TEST_CASE("SortedList: Testing size", "[sorted list]")
{
  SortedList<char> lst;

  REQUIRE(lst.isEmpty());
  REQUIRE(lst.getLength() == 0);

  lst.insert('b');
  REQUIRE(!lst.isEmpty());
  REQUIRE(lst.getLength() == 1);

  lst.insert('a');
  REQUIRE(lst.getLength() == 2);

  lst.removeAt(1);
  REQUIRE(lst.getLength() == 1);

  lst.removeAt(1);
  REQUIRE(lst.getLength() == 0);
  REQUIRE(lst.isEmpty());
}

TEST_CASE("SortedList: Testing insert", "[sorted list]")
{
  SortedList<char> lst;

  char c = 'a';
  while (c <= 'z')
  {
    lst.insert(c);
    ++c;
  }
  REQUIRE(lst.getLength() == 26);

  bool getEntryCheck;
  for (int i = 1; i <= 26; ++i)
  {
    getEntryCheck = (lst.getEntry(i) == 'a' + i - 1); // Note the small change!
    if (!getEntryCheck)
    {
      break;
    }
  }
  REQUIRE(getEntryCheck);
}

TEST_CASE("SortedList: Testing remove", "[sorted list]")
{
  SortedList<char> lst;

  char c = 'a';
  int size = 10;
  while (c < 'a' + size)
  {
    lst.insert(c);
    ++c;
  }
  REQUIRE(lst.getLength() == size);

  lst.remove('c');
  REQUIRE(lst.getLength() == size - 1);
  REQUIRE(lst.getEntry(3) == 'd');

  lst.remove('e');
  REQUIRE(lst.getLength() == size - 2);
  REQUIRE(lst.getEntry(6) == 'h');

  lst.remove('a');
  REQUIRE(lst.getLength() == size - 3);
  REQUIRE(lst.getEntry(1) == 'b');
}

TEST_CASE("SortedList: Testing getPosition and repeated items", "[sorted list]")
{
  SortedList<char> lst;

  lst.insert('a');
  lst.insert('d');
  lst.insert('e');
  lst.insert('c');
  lst.insert('b');
  lst.insert('e');
  lst.insert('f');
  lst.insert('e');

  REQUIRE(lst.getLength() == 8);
  REQUIRE(lst.getPosition('a') == 1);
  REQUIRE(lst.getPosition('b') == 2);
  REQUIRE(lst.getPosition('c') == 3);
  REQUIRE(lst.getPosition('d') == 4);
  REQUIRE(lst.getPosition('e') == 5);
  REQUIRE(lst.getPosition('f') == 8);

  lst.clear();
  REQUIRE_THROWS(lst.getPosition('a'));
}

TEST_CASE("SortedList: Testing constructor from unsorted list", "[sorted list]")
{
  List<char> unsorted;

  unsorted.insert(1, 'a');
  unsorted.insert(2, 'd');
  unsorted.insert(3, 'e');
  unsorted.insert(4, 'c');
  unsorted.insert(5, 'b');

  SortedList<char> sorted(unsorted);

  REQUIRE(sorted.getPosition('a') == 1);
  REQUIRE(sorted.getPosition('b') == 2);
  REQUIRE(sorted.getPosition('c') == 3);
  REQUIRE(sorted.getPosition('d') == 4);
  REQUIRE(sorted.getPosition('e') == 5);
}

TEST_CASE("SortedList: Testing list and sorted list std::out_of_range exceptions", "[sorted list]")
{
  List<char> lst;

  REQUIRE_THROWS_AS(lst.remove(1), std::out_of_range);
  REQUIRE_THROWS_AS(lst.insert(2, 'a'), std::out_of_range);
  REQUIRE_THROWS_AS(lst.getEntry(1), std::out_of_range);
  REQUIRE_THROWS_AS(lst.setEntry(1, 'a'), std::out_of_range);

  lst.insert(1, 'a');
  lst.insert(2, 'b');

  REQUIRE_THROWS_AS(lst.remove(3), std::out_of_range);
  REQUIRE_THROWS_AS(lst.insert(4, 'c'), std::out_of_range);
  REQUIRE_THROWS_AS(lst.getEntry(3), std::out_of_range);
  REQUIRE_THROWS_AS(lst.setEntry(3, 'c'), std::out_of_range);

  SortedList<char> sorted;
  sorted.insert('a');
  sorted.insert('b');
  sorted.insert('c');
  sorted.insert('d');
  sorted.insert('e');

  REQUIRE_THROWS_AS(sorted.removeAt(6), std::out_of_range);
  REQUIRE_THROWS_AS(sorted.getEntry(6), std::out_of_range);
  REQUIRE_THROWS_AS(sorted.getEntry(0), std::out_of_range);
  REQUIRE_THROWS_AS(sorted.removeAt(-1), std::out_of_range);
}

/* Your tests here */

TEST_CASE("sortedlist testing insertion order and duplicates", "[sorted list]")
{
  SortedList<int> firefighter;
  
  firefighter.insert(5);
  firefighter.insert(3);
  firefighter.insert(8);
  firefighter.insert(3);
  firefighter.insert(10);
  firefighter.insert(1);

  REQUIRE(firefighter.getLength() == 6);
  REQUIRE(firefighter.getEntry(1) == 1);
  REQUIRE(firefighter.getEntry(2) == 3);
  REQUIRE(firefighter.getEntry(3) == 3);
  REQUIRE(firefighter.getEntry(4) == 5);
  REQUIRE(firefighter.getEntry(5) == 8);
  REQUIRE(firefighter.getEntry(6) == 10);
}

TEST_CASE("sortedlist testing remove edge cases", "[sorted list]")
{
  SortedList<int> truck;

  truck.insert(2);
  truck.insert(4);
  truck.insert(6);
  truck.insert(8);

  REQUIRE(truck.getLength() == 4);
  
  truck.remove(2);
  REQUIRE(truck.getLength() == 3);
  REQUIRE(truck.getEntry(1) == 4);
  
  truck.remove(8); 
  REQUIRE(truck.getLength() == 2);
  REQUIRE(truck.getEntry(2) == 6);
  
  truck.remove(4);
  REQUIRE(truck.getLength() == 1);
  REQUIRE(truck.getEntry(1) == 6);
  
  truck.remove(6); 
  REQUIRE(truck.isEmpty());
}

TEST_CASE("sortedlist testing getposition exceptions", "[sorted list]")
{
  SortedList<int> engine;

  engine.insert(10);
  engine.insert(20);
  engine.insert(30);
  
  REQUIRE(engine.getPosition(10) == 1);
  REQUIRE(engine.getPosition(20) == 2);
  REQUIRE(engine.getPosition(30) == 3);
  
  REQUIRE_THROWS_AS(engine.getPosition(15), std::invalid_argument);
  REQUIRE_THROWS_AS(engine.getPosition(40), std::invalid_argument);
}

TEST_CASE("sortedlist testing insert into empty list", "[sorted list]")
{
  SortedList<std::string> ladder;
  
  ladder.insert("firefighter");
  REQUIRE(ladder.getLength() == 1);
  REQUIRE(ladder.getEntry(1) == "firefighter");
}

TEST_CASE("sortedlist testing insert with same elements", "[sorted list]")
{
  SortedList<char> ladder;

  ladder.insert('x');
  ladder.insert('x');
  ladder.insert('x');

  REQUIRE(ladder.getLength() == 3);
  REQUIRE(ladder.getEntry(1) == 'x');
  REQUIRE(ladder.getEntry(2) == 'x');
  REQUIRE(ladder.getEntry(3) == 'x');
}


TEST_CASE("sortedlist testing edge cases", "sorted list")
{
  SortedList<int> engine;

  engine.insert(1000000);
  engine.insert(-1000000);
  engine.insert(0);

  REQUIRE(engine.getLength() == 3);
  REQUIRE(engine.getEntry(1) == -1000000);
  REQUIRE(engine.getEntry(2) == 0);
  REQUIRE(engine.getEntry(3) == 1000000);
  
  REQUIRE_THROWS_AS(engine.remove(500), std::invalid_argument);
  REQUIRE_THROWS_AS(engine.remove(-500), std::invalid_argument);
  
  engine.insert(1000000);
  engine.insert(-1000000);
  REQUIRE(engine.getLength() == 5);
}