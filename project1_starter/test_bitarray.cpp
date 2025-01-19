#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include <iostream>
#include "bitarray.hpp"
#include "bitarray.cpp"

TEST_CASE("Bitarray: Test default construction and asString", "[bitarray]")
{
    BitArray b;
    REQUIRE(b.size() == 8);
    REQUIRE(b.good());
    REQUIRE(b.asString().compare("00000000") == 0);
}

TEST_CASE("Bitarray: Test construction with asString", "[bitarray]")
{
    BitArray b;
    REQUIRE(b.asString().compare("00000000") == 0);
}

TEST_CASE("Bitarray: Test construction size and asString", "[bitarray]")
{
    // You can construct a string s of as s(n, c)
    // where n is the number of characters and c is the character
    std::string s(64, '0');
    BitArray b(64);
    REQUIRE(b.size() == 64);
    REQUIRE(b.good());
    REQUIRE(b.asString().compare(s) == 0);
}

TEST_CASE("Bitarray: Test construction std::string and asString", "[bitarray]")
{
    std::string s("00101110000011000001101000001");
    BitArray b(s);
    REQUIRE(b.size() == s.size());
    REQUIRE(b.good());
    REQUIRE(b.asString().compare(s) == 0);
}

TEST_CASE("Bitarray: Test construction invalid std::string", "[bitarray]")
{
    std::string s("00101110000011002001101000001");
    BitArray b(s);
    REQUIRE_FALSE(b.good());
}

TEST_CASE("Bitarray: Test set method", "[bitarray]")
{
    std::string s("00010001");
    BitArray b;
    b.set(3);
    b.set(7);
    REQUIRE(b.size() == 8);
    REQUIRE(b.good());
    REQUIRE(b.asString().compare(s) == 0);

    std::string s1("00010");
    BitArray b1(5);
    b1.set(3);
    REQUIRE(b1.size() == 5);
    REQUIRE(b1.good());
    REQUIRE(b1.asString().compare(s1) == 0);
}

TEST_CASE("Bitarray: Test many given methods combined", "[bitarray]")
{
    // << is the left shift operator for integers
    // e.g., 1 << 8 is 2^8=256, 1<<15 is 2^15=32768
    std::string s((1 << 15) + 3, '0');
    BitArray b(s);
    REQUIRE(b.size() == s.size());
    REQUIRE(b.good());
    REQUIRE(b.asString().compare(s) == 0);

    for (int i = 1; i < (1 << 10); i++)
    {
        b.set(i);
        b.reset(i + (1 << 10));
        b.toggle(i + (1 << 11));
        REQUIRE(b.good());
        REQUIRE(b.test(i));
        REQUIRE_FALSE(b.test(i + (1 << 10)));
        REQUIRE((
            (b.test(i + (1 << 11)) == true && s.at(i + (1 << 11)) == '0') || // either this is true
            (b.test(i + (1 << 11)) == false && s.at(i + (1 << 11)) == '1')   // or this is true

            ));
    }
}

//additional test cases for the recent implementations in bitarray.cpp
//4 additionals needed 1 for test, reset, toggle, and as string


//test implementation test cases


TEST_CASE("BitArray: Test 'test' method","[bitarray]"){
    BitArray b(10);
    b.set(6);
    REQUIRE(b.test(6));
    REQUIRE_FALSE(b.test(2));
    REQUIRE_FALSE(b.test(9));

}

TEST_CASE("BitArray: Test 'reset' method","[bitarray]"){
    BitArray b(12);
    b.set(8);
    b.set(4);
    REQUIRE(b.test(8));
    REQUIRE(b.test(4));
    b.reset(8);
    REQUIRE_FALSE(b.test(8));
    REQUIRE(b.test(4));

}

TEST_CASE("BitArray: Test 'toggle' method","[bitaray]"){
    BitArray b(15);
    b.toggle(7);
    b.toggle(10);
    REQUIRE(b.test(7));
    REQUIRE(b.test(10));
    b.toggle(7);
    REQUIRE_FALSE(b.test(7));
    REQUIRE(b.test(10));
}

TEST_CASE("BitArray: Test 'asString' method","[bitarray]"){
    BitArray b(16);
    b.set(0);
    b.set(5);
    b.set(15);
    REQUIRE(b.asString().compare("1000010000000001")==0);
    b.reset(0);
    REQUIRE(b.asString().compare("0000010000000001")==-1);
}

