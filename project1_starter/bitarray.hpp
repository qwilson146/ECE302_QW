#ifndef BITARRAY_HPP
#define BITARRAY_HPP
#include <stdint.h>
#include <stdlib.h>
#include <string>

#include "bitset.hpp"

class BitArray : public Bitset
{
public:
  BitArray();

  BitArray(intmax_t size);

  BitArray(const std::string &value);

  ~BitArray();

  BitArray(const BitArray &) = delete;
  BitArray &operator=(const BitArray &) = delete;

  intmax_t size() const;

  bool good() const;

  void set(intmax_t index);

  void reset(intmax_t index);

  void toggle(intmax_t index);

  bool test(intmax_t index);

  std::string asString() const;

  int countones() const;
  

  

private:
  // TODO

  uint8_t *point; //remember this pointe
  intmax_t numbits; //number of bits
  bool Valid; //checks if bitset can be valid (t or f)
  
};



#endif