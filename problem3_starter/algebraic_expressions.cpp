#include <string>
#include <iostream>
#include <cctype> // for isalpha

#include "algebraic_expressions.hpp"

bool isoperator(char ch)
{
  return ((ch == '+') || (ch == '-') || (ch == '/') || (ch == '*'));
}

int endPost(std::string s, int last)
{
  int first = 0;
  if (first > last) // invalid index for last
  {
    return -1;
  }

  char ch = s[last];
  if (isalpha(ch))
  {
    return last; // if last is an operator, then the end of the post-fix expression is just itself
  }
  else
  {
    if (isoperator(ch)) // can be omitted, but just to make sure that the last character is an operator
    {
      int lastEnd = endPost(s, last - 1); // search for the "start" (in human eyes) of first post-fix expression before ch
      if (lastEnd > -1)
      {
        return endPost(s, lastEnd - 1); // search for the "start" (in human eyes) of the second post-fix expression before ch
      }
      else
      {
        return -1;
      }
    }
    else
    {
      return -1;
    }
  }
}

bool isPost(std::string s)
{
  int firstChar = endPost(s, s.size() - 1);
  // same as prefix validarity check, postfix expression is valid if and only if
  // the post-fix expression range of the last ch happens to include until the first character
  return (firstChar == 0);
}



//below is the TODO of the convert functionality




void convert(const std::string &postfix, std::string &prefix)
{
  //checking if the given post is valid if not it throws an invalid
  //argument error as seen below
  if(!isPost(postfix)){
    throw std::invalid_argument("Invalid postfix expression");

  }

  //this is a testing if the expression contains one operator
  if(postfix.size()==1){
    //checking to make sure the operator is valid (the character is the operand)
    if(isalpha(postfix[0])){
      //assigning th op to prefix so there is not conversion needed yet

      prefix =postfix;
      //empty return to get out of the loop
      return;

    }
    else{
      //throws an invalid argument error if an op is not found in the expression

      throw std::invalid_argument("invalid expression");

    }
  }

  //recursion here- this converts the expression
  char lastChar = postfix[postfix.size()-1];
  // this if statement checks if the last char
  //is an op. if it is not, the invalid expression error will be thrown
  //to indicate
  if (!isoperator(lastChar)){
    throw std::invalid_argument("invalid expression");

  }
  //finding if there is a second operand in the expression
  int lastOperand = endPost(postfix,postfix.size()-2);
  //if there is not an operand found (-1 used in this case cause if there were 
  //2 operands it would return 0 which would not be correct so -1 is used)
  //there will be an invalid argument error thrown to indicate that there was not more than
  //1 op in the expression given

  if(lastOperand==-1){
    throw std::invalid_argument("invalid expression");
  }


  //this splits the post fix into two parts (left and right) 0-last then last-post -last-1 to correctly size
  //in order to achieve the split correctly
  //this is the left substring and the right substring respectively 
  std::string leftpostfix=postfix.substr(0,lastOperand);
  std::string rightpostfix = postfix.substr(lastOperand,postfix.size()-lastOperand-1);


  //declared left and right prefixes which will be used to convert the vonverted
  //prefix expressios from the previous lines of code

  std::string leftprefix;
  std::string rightprefix;

  //now converting the expressions from post to pre notation
  convert(leftpostfix,leftprefix);
  convert(rightpostfix,rightprefix);


  //finally setting everything back into one whole expression in the 
  //prefix format which is the operator , left fix, and right fix
  
  prefix=lastChar+leftprefix+rightprefix;
  

}