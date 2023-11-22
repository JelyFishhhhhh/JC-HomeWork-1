#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <fstream>
using std::ifstream;
using std::ofstream;
using std::ios;

struct string
{
   size_t size = 0;
   char *charArray = new char[ 21 ]();
};

// prints all English words which are contiguous substrings of inputtedWord into a file
void embeddedWords( string &dictionaryWord, string &inputtedWord );

// returns true if and only if dictionaryWord is a substring of inputtedWord
bool isSubstring( string &dictionaryWord, string &inputtedWord );

int main()
{
   string inputtedWord;
   cout << "Enter a word: ";
   cin >> inputtedWord.charArray;
   inputtedWord.size = strlen( inputtedWord.charArray );

   string dictionaryWord;

   embeddedWords( dictionaryWord, inputtedWord );

   system( "pause" );
}