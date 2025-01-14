#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "add.hpp"

// force template expansion
template class Add<int>;

TEST_CASE("Test add", "[Add]"){

  Add<int> a;
  REQUIRE(a.call(1,2)==3);
}

//add the 5 required test cases here



//answer the two other questions here in comments
//now seeing if they will update automatically
