// Project 3 -- XML Parser

/** @file XMLParser.cpp */

#include <string>
#include "XMLParser.hpp"

//gave the assignment my best shot due to other commitments that 

XMLParser::XMLParser()
{
	// TODO
	clear(); //checking to make sure all data is reset when an object in initialized
} // end default constructor

// Then finish this function to pass the 4th~6th unit tests
bool XMLParser::tokenizeInputString(const std::string &inputString)
{
	// TODO, use '<' and '>' as anchors to scan string; Remember to clear each time before
	// tokenizing a new string, and refer to the following code structure:

	// for (char c : inputString)
	// {
	// 	if (c == '<') {?? continue;}
	// 	else if (c == '>') {?? continue;}
	// 	else {?? continue;}
	// }
	// Reset previous data before tokenization
	clear();
	size_t index = 0;

    // Iterate through the string character by character
    for (char c : inputString)
    {
        if (c == '<') // Start of a tag
        {
            size_t closing = index;
            // Find the corresponding closing '>'
            while (closing < inputString.size() && inputString[closing] != '>')
            {
                closing++; //incrementing to find the >
            }
            if (closing == inputString.size()) // no closing '>'
            {
				//return false if > is missing
                return false;
            }
			//extraction tag
            std::string tag = inputString.substr(index, closing - index + 1);
            TokenStruct token; //struc to store token

            // Determine whether the tag is a start tag, end tag, or empty tag
            if (tag[1] == '/')//second char is / its an end tag
            {
                token.tokenType = END_TAG;
                token.tokenString = tag.substr(2, tag.length() - 3);//extract name
            }
            else if (tag[tag.length() - 2] == '/')//if 2nd is / its empty
            {
                token.tokenType = EMPTY_TAG;
                token.tokenString = tag.substr(1, tag.length() - 3);//extract name
            }
            else//else its a start
            {
                token.tokenType = START_TAG;
                token.tokenString = tag.substr(1, tag.length() - 2);//extracting name
            }

            tokenizedInputVector.push_back(token);//store token in vec
            index = closing + 1;//moving past >
        }
        else if (c == '>') // Ignore closing tag '>'
        {
            continue;
        }
        else // Content (not part of a tag)
        {
            size_t ntag = index;
            // Find the next '<' to identify the end of the content
            while (ntag < inputString.size() && inputString[ntag] != '<')
            {
				//move to find the next tag
                ntag++;
            }

            std::string data = inputString.substr(index, ntag - index);//extract
            TokenStruct token;
            token.tokenType = CONTENT;
            token.tokenString = data;
            tokenizedInputVector.push_back(token);//storing token 
            index = ntag;//setting the index to next tag position
        }
    }

    return true;//return if tokenization is true
	
} // end

// Then finish this function to pass the 7th~9th unit test
bool XMLParser::parseTokenizedInput()
{
	// TODO, iterate through tokenizedInputVector to check validity
	// and update stack and bag accordingly, and refer to the following code structure:

	// for (int i = 0; i < tokenizedInputVector.size(); i++)
	// {
	//   if (?? == START_TAG) {?? continue;}
	// 	 else if (?? == END_TAG) {?? continue;}
	// 	 else if (?? == EMPTY_TAG) {?? continue;}
	// 	 ...
	// 
	//iteration through token to check if valid
	for (size_t i = 0; i < tokenizedInputVector.size(); ++i)
    {
		//getting current token
        TokenStruct token = tokenizedInputVector[i];

        if (token.tokenType == START_TAG || token.tokenType == EMPTY_TAG)
        {
            // Push the element onto the stack and add to the bag
            parseStack.push(token.tokenString);
			//adding used for frequency
            elementNameBag.add(token.tokenString);
        }
        else if (token.tokenType == END_TAG)
        {
            // Check if the closing tag matches the last opened tag in the stack
            if (!parseStack.isEmpty() && parseStack.peek() == token.tokenString)
            {
                parseStack.pop(); // Pop the stack if tags match
            }
            else
            {
                return false; // Mismatched tags
            }
        }
    }

    // If the stack is not empty, we have unclosed tags
    return parseStack.isEmpty();
	
}

	


void XMLParser::clear()
{
	// TODO
	//clearing all respective
	tokenizedInputVector.clear();
	elementNameBag.clear();
	parseStack.clear();
}

std::vector<TokenStruct> XMLParser::returnTokenizedInput() const
{
	return tokenizedInputVector;//return vector of parsed tikens
}

bool XMLParser::containsElementName(const std::string &element) const
{
	// TODO
	if (tokenizedInputVector.empty())
	{
		throw std::logic_error("Input must be tokenized and parsed first.");
	}

	return elementNameBag.contains(element);
}

int XMLParser::frequencyElementName(const std::string &element) const
{
	// TODO
	// Throw std::logic_error if either tokenizeInputString() or parseTokenizedInput() returns false
	// If Bag is updated correctly, this should be as simple as one line.
	if (tokenizedInputVector.empty())
    {
        throw std::logic_error("Input must be tokenized / parsed first.");
    }

    // Initialize count to 0
    int count = 0;

    // Iterate over the tokenized input
    for (size_t i = 0; i < tokenizedInputVector.size(); ++i)
    {
        TokenStruct token = tokenizedInputVector[i];

        // Only check START_TAG and EMPTY_TAG, as these represent element names
        if ((token.tokenType == START_TAG || token.tokenType == EMPTY_TAG) && token.tokenString == element)
        {
            count++; // Increment the count when we find a matching element name
        }
    }
	//returning the cound of char
    return count;
	
}