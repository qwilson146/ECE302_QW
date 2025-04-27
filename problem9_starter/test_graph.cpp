#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "graph.hpp"

TEST_CASE("Test Construction", "[construction]")
{
  Graph<int> g;
  REQUIRE(g.getNumVertices() == 0);
  REQUIRE(g.getNumEdges() == 0);
}
// additional test cases


TEST_CASE("Test Add Edge", "[add]") {
  Graph<int> g;
  REQUIRE_FALSE(g.add(1, 2));

  g.add(1, 3);  // 1 and 3 now exist
  REQUIRE(g.getNumVertices() == 2);
  REQUIRE(g.getNumEdges() == 1);

  REQUIRE(g.add(1, 2)); // 1 exists, add 2
  REQUIRE(g.getNumVertices() == 3);
  REQUIRE(g.getNumEdges() == 2);

  REQUIRE_FALSE(g.add(1, 2));

  REQUIRE_FALSE(g.add(2, 2));
}

TEST_CASE("Test Remove Edge", "[remove]") {
  Graph<int> g;

  g.add(1, 2);
  g.add(2, 3);
  g.add(3, 1);

  REQUIRE(g.getNumEdges() == 3);

  REQUIRE(g.remove(1, 2));
  REQUIRE(g.getNumEdges() == 2);
  REQUIRE(g.getNumVertices() == 3);

  REQUIRE_FALSE(g.remove(1, 2));

  g.remove(2, 3);
  g.remove(3, 1);

  REQUIRE(g.getNumEdges() == 0);
  REQUIRE(g.getNumVertices() == 0);
}

TEST_CASE("Test getNumVertices and getNumEdges", "[query]") {
  Graph<int> g;
  g.add(10, 20);
  g.add(20, 30);
  g.add(10, 30);

  REQUIRE(g.getNumVertices() == 3);
  REQUIRE(g.getNumEdges() == 3);
}

TEST_CASE("Add and Remove Combo", "[combo]") {
  Graph<int> g;
  g.add(1, 2);
  g.add(2, 3);
  g.add(3, 4);

  REQUIRE(g.getNumEdges() == 3);
  REQUIRE(g.getNumVertices() == 4);

  g.remove(2, 3);
  REQUIRE(g.getNumEdges() == 2);
  REQUIRE(g.getNumVertices() == 4); 

  g.remove(1, 2);
  g.remove(3, 4);

  REQUIRE(g.getNumEdges() == 0);
  REQUIRE(g.getNumVertices() == 0); 
}