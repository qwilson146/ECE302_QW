#ifndef BITSET_HPP
#define BITSET_HPP
#include <stdint.h>
#include <string>

/**
 * @author Gavin and Quentin??
 * @file 
 * @brief A class that represents a bitset with ways to manipulate each bit
 */



class Bitset
{
public:
  virtual ~Bitset() {}; // virtual destructor, no need to comment



  // TODO COMMENT
  /** returns size of bitset
   * 
   * @param None
   * @pre the bitset must have an initial value
   * @post None
   * @return True if bitset is valid, will return false if anything else
   * @throw none
  */
  virtual intmax_t size() const = 0;



  // TODO COMMENT
  /** Will see if the bitset is valid
   * 
   * @param index The index of the bit eg []
   * @pre the index must be within the scope
   * @post  the specified bit index value will be 1
   * @return none
   * @throw none
   */
  virtual bool good() const = 0;



  // TODO COMMENT

  /** sets bit at the index given to 1
   * 
   * @param index the index of the bit you want
   * @pre index must be within the scope
   * @post the bit at that index point will become 1
   * @return none
   * @throw none
   */

  virtual void set(intmax_t index) = 0;



  // TODO COMMENT
  /** will reset the bit at the index listed to the value of 0
   * 
   * @param index the index of the bit you would like to reset
   * @pre the index must be in the scope
   * @post the bit at the index chosen will be val 0
   * @return none
   * @throw none
   */
  virtual void reset(intmax_t index) = 0;



  // TODO COMMENT
  /** will toggle the value at the index given (flips val from 0 to 1 or 1 to 0)
   * 
   * @param index the index of the bit you would like to toggle
   * @pre the index must be in the scope
   * @post the bits value will be toggled to the other value
   * @return none
   * @throw none
   */
  virtual void toggle(intmax_t index) = 0;

  // TODO COMMENT
  /** will test the bit at the given index
   * 
   * @param index you need the index of the bit youd like to test
   * @pre the index must be in the scope
   * @post none
   * @return true if the val of the bit is 1 or false if the bit is val 0
   * @throw none

   */
  virtual bool test(intmax_t index) = 0;

  // TODO COMMENT
  /** returns the string rep of the bitset 
   * 
   * @param none
   * @pre the bitset is initialized
   * @post none
   * @return the string equivalent of the bitset, each char will rep a bit
   * @throw none
  
  */
  virtual std::string asString() const = 0;
};

#endif
