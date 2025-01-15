#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "add.hpp"

// force template expansion
template class Add<int>;

TEST_CASE("Test add", "[Add]"){

  Add<int> a;
  REQUIRE(a.call(1,2)==3);

  SECTION("long test"){
    Add<long>addlong;
    REQUIRE(addlong.call(123456789,987654321)==1111111110);

  }

  SECTION("double test"){
    Add<double>adddouble;
    double sqrt2=std::sqrt(2);
    REQUIRE(adddouble.call(3-sqrt2,4+sqrt2)==Approx(7.0));

  }

  SECTION("char test"){
    Add<char>addchar;
    REQUIRE(addchar.call('2','3')=='e');

  }

  SECTION("string test"){
    Add<std::string>addstring;
  REQUIRE(addstring.call(std::string("2"),std::string("3"))=="23");

  }

  SECTION("bool test"){
    Add<bool>addbool;
    REQUIRE(addbool.call(true,true)==true);
  }
}




// questions 6 will be answered below:


//Q6 p1
//The feature of the add class that remains untested despite the existing unit test developed
//above is very very small and very very large numbers as well as any
//addition that includes overflows and values that are not numerical
//eg char string and bool like scene above.  They do not add like regular number
//but rather each in their own individual way which is not accounted for in the add class

//Q6 p2
//No there is not any operator overloading in this add class that was defined
//In the add class only the call() method is used to do the addition in the test cases
//If we wanted to overload to be included we would have to redefine our operators so they can
//behave differently to account for the overloading