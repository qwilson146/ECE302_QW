#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include <string>

#include "algebraic_expressions.hpp"

/* Provided test cases */
TEST_CASE("Test endPost", "[postpre]")
{
  std::string postfix_valid = "ab+";
  int test_idx_valid = 0;
  std::string postfix_invalid = "+";
  int test_idx_invalid = -1;
  REQUIRE(endPost(postfix_valid, postfix_valid.length() - 1) == test_idx_valid);
  REQUIRE(endPost(postfix_invalid, postfix_invalid.length() - 1) == test_idx_invalid);
}

TEST_CASE("Test isPost", "[postpre]")
{
  std::string postfix_valid = "ab+";
  std::string postfix_invalid = "+ab";

  REQUIRE(isPost(postfix_valid));
  REQUIRE_FALSE(isPost(postfix_invalid));
}

TEST_CASE("Postpre: Test expression ab+", "[postpre]")
{
  std::string postfix = "ab+";
  std::string prefix = "";
  std::string test = "+ab";

  REQUIRE_NOTHROW(convert(postfix, prefix));

  REQUIRE(prefix == test);
}

TEST_CASE("Postpre: Test other operators", "[postpre]")
{
  std::string postfix = "ab-";
  std::string prefix = "";
  std::string test = "-ab";

  REQUIRE_NOTHROW(convert(postfix, prefix));
  REQUIRE(prefix == test);

  postfix = "ab*";
  prefix = "";
  test = "*ab";
  REQUIRE_NOTHROW(convert(postfix, prefix));
  REQUIRE(prefix == test);

  postfix = "ab/";
  prefix = "";
  test = "/ab";
  REQUIRE_NOTHROW(convert(postfix, prefix));
  REQUIRE(prefix == test);
}

/* TODO: Your test cases here */


TEST_CASE("testing end post function again with different exp","[postpre]"){
  std::string postfix_valid="abc*+";
  int test_valid=0;
  int test_invalid=-1;
  std::string postfix_invalid= "a+";
  REQUIRE(endPost(postfix_valid,postfix_valid.length()-1)==test_valid);
  REQUIRE(endPost(postfix_invalid,postfix_invalid.length()-1)==test_invalid);

}

TEST_CASE("converting long expressions","[postpre]"){
  std::string postfix = "mnop*-q+";
  std::string prefix = "";
  std::string test = "+-*mnopq";

  REQUIRE_NOTHROW(convert(postfix, prefix));
  REQUIRE(prefix == test);
}

TEST_CASE("testing multiple operators","[postpre]"){

  std::string postfix = "uv+wx-*";
  std::string prefix = "";
  std::string test = "-*+uvwx";

  REQUIRE_NOTHROW(convert(postfix, prefix));
  REQUIRE(prefix == test);
}


TEST_CASE("testing mixed operations","[postpre]"){
  std::string postfix = "rs+tu*/v-";
  std::string prefix = "";
  std::string test = "-/*+rstuv";

  REQUIRE_NOTHROW(convert(postfix, prefix));
  REQUIRE(prefix == test);
}

TEST_CASE("invalid expressions test","postpre"){
  std::string postfix_invalid1 = "x+y";
  std::string prefix;
  REQUIRE_THROWS_AS(convert(postfix_invalid1, prefix), std::invalid_argument);

  std::string postfix_invalid2 = "-yz";
  REQUIRE_THROWS_AS(convert(postfix_invalid2, prefix), std::invalid_argument);
}