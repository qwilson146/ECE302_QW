#include <string>
#include <vector>
#include <iostream>
#include "FindPalindrome.hpp"

using namespace std;

//------------------- HELPER FUNCTIONS -----------------------------------------

// non-class helper functions go here, should be declared as "static" so that
// their scope is limited

//this function will combine all the strings given into one concatenated string (no spaces)
static string combinedstringvec(const vector<string>& stringVector){
	string combinedstring="";
	for(int i=0;i<stringVector.size();i++){
		//this will actually combine the strings together into one
		combinedstring+=stringVector[i];

	}
	//returns the final combined string
	return combinedstring;

}

//this function calculates the freq of each character in the string (a-z)
static vector<int> getcharfreq(const vector<string>& stringVector){
	//this is a vector of 26 zeros (1 for each letter in the alphabet)
	//the zeros are the frequency of each char appearance
	vector<int> freq(26,0);
	for(int i=0; i<stringVector.size();i++){
		for (int j = 0; j < stringVector[i].size(); j++) {
            char c = stringVector[i][j];//this will get each character from the string
			if(isalpha(c)){ //this is checking is char c (arbitrary name) is alphabetical (ie not num or symbol)

				freq[tolower(c)-'a']++;//incrementation of the frequency
			}
        }
	}
	return freq;//returns the vector of frequency
}

//this next function was given
// helper function to convert string to lower case
static void convertToLowerCase(string & value)
{
	for (int i=0; i<value.size(); i++) {
		value[i] = tolower(value[i]);
	}
}

//------------------- PRIVATE CLASS METHODS ------------------------------------

// private recursive function. Must use this signature!
void FindPalindrome::recursiveFindPalindromes(vector<string>
        candidateStringVector, vector<string> currentStringVector)
{
	// TODO need to implement this recursive function!
	//recursively finds the palindromes from the vector of candidates
	if(candidateStringVector.empty()){
		//if there are no candidates left to go through it will then check if that
		//given combination is a palindrome.
		string combinedstring = combinedstringvec(currentStringVector);
		if(isPalindrome(combinedstring)){
			palindromes.push_back(currentStringVector);//this will add the combination (if its a palindrome) to the result


		}
		return;//return to get back to the previous recursion
	}

	//recursive callt o get all combinations of the cand strings
	for(int i=0; i<candidateStringVector.size();i++){
		vector<string> nextcan =candidateStringVector;//copying candidate vec
		vector<string> nextcurrentstring=currentStringVector;//pying the the current string comb
		nextcan.erase(nextcan.begin()+i);//removing the current string from the candidates list
		nextcurrentstring.push_back(candidateStringVector[i]);//adding that string to the combinations you currently have
		recursiveFindPalindromes(nextcan,nextcurrentstring);//recusrion with the new vectors

	}

	
}

// private function to determine if a string is a palindrome (given, you
// may change this if you want)
//did not change this function (left it as is and made no changes or additions)
bool FindPalindrome::isPalindrome(string currentString) const
{
	locale loc;
	// make sure that the string is lower case...
	convertToLowerCase(currentString);
	// see if the characters are symmetric...
	int stringLength = currentString.size();
	for (int i=0; i<stringLength/2; i++) {
		if (currentString[i] != currentString[stringLength - i - 1]) {
			return false;
		}
	}
	return true;
}


//------------------- PUBLIC CLASS METHODS -------------------------------------

FindPalindrome::FindPalindrome()
{
	// TODO need to implement this...
	//should not need anything here as the vectors are already
	//initialized so there is nothing to add
}

FindPalindrome::~FindPalindrome()
{
	// TODO need to implement this...
	//this is the destructor and it clears the vectors to clear memory
	words.clear();
	palindromes.clear();
}

int FindPalindrome::number() const
{
	// TODO need to implement this...
	//returns the size of the palindrome vector
	return palindromes.size();
}

void FindPalindrome::clear()
{
	// TODO need to implement this...
	//clearing the words and palindromes to reset the initial object
	words.clear();
	palindromes.clear();

}

bool FindPalindrome::cutTest1(const vector<string> & stringVector)
{
	// TODO need to implement this...
	//get the frequency of characters in the vector
	vector<int> freq =getcharfreq(stringVector);
	//initializing the odd count to 0
	int count = 0;
	for (int i=0;i<freq.size();i++){
		if(freq[i]%2 !=0){
			count++;//this will increment the count of characters that have an odd freq

		}
	}
	return count<=1;//a valid pal can have a max of ONE character with an odd frequency

}

bool FindPalindrome::cutTest2(const vector<string> & stringVector1,
                              const vector<string> & stringVector2)
{
	// TODO need to implement this...

	//getting the frequency from strings 1 and 2
	vector<int> freq1 =getcharfreq(stringVector1);
	vector<int> freq2 =getcharfreq(stringVector2);
	//loop through all 26 characters (a-z)
	for (int i=0;i<26;i++){
		if(freq1[i]>freq2[i]){
			return false;//will return false if freq 1 (string 1) is higher than freq 2 (str 2)
		}
	}
	return true;//will return true if the string freq 1 does not exceed 2s
}

bool FindPalindrome::add(const string & value)
{
	// TODO need to implement this...
	//adds a single string to the list of words
	string lowerValue=value;
	convertToLowerCase(lowerValue);//converts the string to lowercase by using the helper function

	for (int i = 0; i < lowerValue.length(); i++) {
        if (!isalpha(lowerValue[i])) {
            return false; //if the string has any non alphabetic characters (num , sym etc) it will return false
        }
    }
	//this is checking for duplicates in the list (this is also case sensitive)
	for(int i=0;i<words.size();i++){
		string lowerWord=words[i];
		convertToLowerCase(lowerWord);
		if(lowerWord==lowerValue){
			return false;//if the word is duplicate (ie already there) it will return false

		}
	}

	
	words.push_back(value);//add the word to the list
	palindromes.clear();//clearing the current palindrome since the words could have changed
	recursiveFindPalindromes(words,{});//calling the recursive function to find the new palindrome
	return true;// will return true if the word gets added.

}

bool FindPalindrome::add(const vector<string> & stringVector)
{
	//TODO need to implement this...
	//this adds a vector of strings to the list of words
	for (int i = 0; i < stringVector.size(); i++) {
        string lowerValue = stringVector[i];//copy words to temp string
        convertToLowerCase(lowerValue);//convertings to lowercase by helper function
		//checking if the word already exists
        for (int j = 0; j < words.size(); j++) {
            string lowerWord = words[j];
            convertToLowerCase(lowerWord);//convert to lowercase
            if (lowerWord == lowerValue) {
                return false; //if the word is already presence it will return false
            }
        }

		//checking for diblicates wiehin the vector
        for (int k = 0; k < stringVector.size(); k++) {
            if (k != i) {//ensure it is not hte same index
                string lowerVectorWord = stringVector[k];//copying word
                convertToLowerCase(lowerVectorWord);//converstion to lowercase
                if (lowerVectorWord == lowerValue) {
                    return false;//returning false if dup is found
                }
            }
        }
    }
	//if all the words provided are not dup (unique) they will be added
    for (int i = 0; i < stringVector.size(); i++) {
        words.push_back(stringVector[i]);// accounting for each additional word to the words list
    }
    return true;// return of true if they were added in successfully

	

}
vector< vector<string> > FindPalindrome::toVector() const
{
	return palindromes;//reutn the palindrome as a vector of vector of string
}