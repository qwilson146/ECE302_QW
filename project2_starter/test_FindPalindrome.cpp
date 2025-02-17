#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"
#include "FindPalindrome.cpp"

// There should be at least one test per FindPalindrome method

TEST_CASE( "Test adding words", "[FindPalindrome]" )
{
	FindPalindrome b;
	REQUIRE(b.add("kayak"));
	REQUIRE(!b.add("kayak1"));
}

TEST_CASE("test recursion", "[FindPalindrome]"){
	FindPalindrome b;

	REQUIRE(b.add("a"));
	REQUIRE(b.add("AA"));
	REQUIRE(b.add("AaA"));
	REQUIRE(b.number() == 6);
}

//additional test cases are below
TEST_CASE("valid and invalid words","[FindPalindrome]"){
	FindPalindrome b;
	REQUIRE(b.add("racecar"));
	REQUIRE(!b.add("racecar"));
	REQUIRE(!b.add("number44"));

}



TEST_CASE("recursive finding","[FindPalindrome]"){
	FindPalindrome b;
REQUIRE(b.add("a"));
REQUIRE(b.add("b"));
REQUIRE(b.add("aba"));
REQUIRE(b.number()==6);
}

TEST_CASE("test clear","[FindPalindrome]"){
	FindPalindrome b;
	REQUIRE(b.add("these"));
	REQUIRE(b.add("test"));
	REQUIRE(b.number()>0);
	b.clear();
	REQUIRE(b.number()==0);


}

TEST_CASE("test cut 1","[FindPalindrome]"){
	FindPalindrome b;
	std::vector<std::string> words = {"datas", "level"};
    REQUIRE(b.cutTest1(words)); 
    words.push_back("hello");
    REQUIRE(!b.cutTest1(words));

}

TEST_CASE("test cut 2","[FindPalindrome]"){
	FindPalindrome b;
	std::vector<std::string> words1 = {"datas"};
    std::vector<std::string> words2 = {"datas", "structure"};
    REQUIRE(b.cutTest2(words1, words2)); 
    std::vector<std::string> words3 = {"hi"};
    REQUIRE(!b.cutTest2(words3, words2));

}




TEST_CASE("test adding vector of words","[FindPalindrome]"){
	FindPalindrome b;
	std::vector<std::string> words = {"rotory", "engine"};
    REQUIRE(b.add(words));
    REQUIRE(!b.add(words));
}


TEST_CASE("test to vector output","[FindPalindrome]"){
	FindPalindrome b;
	REQUIRE(b.add("class"));
    std::vector<std::vector<std::string>> results = b.toVector();
    REQUIRE(!results.empty());
    REQUIRE(results.size() >= 1);
}